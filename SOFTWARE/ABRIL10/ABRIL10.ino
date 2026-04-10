#include <Arduino.h>
#include <QTRSensors.h>

// --- Configuración QTR8A ---
#define NUM_SENSORS 8
uint8_t qtrPins[NUM_SENSORS] = {36, 39, 34, 35, 32, 33, 25, 26};
QTRSensors qtr;

// --- TB6612FNG ---
#define BIN1 19
#define BIN2 18
#define AIN2 17
#define AIN1 16
#define PWMB 21
#define PWMA 4

// --- LEDs y botón ---
#define LED_ENCENDIDO 2
#define LED_CALIBRACION 23
#define BOTON_CALIBRAR 13

// --- PID ---
float Kp = 0.35;
float Ki = 0.0;
float Kd = 7.0;

int lastError = 0;
long integral = 0;
const int MAX_PWM = 255;

// --- ESTADOS ---
bool modoSeguir = false;
bool calibrando = false;

// --- CONTROL DINÁMICO DE VELOCIDAD ---
int velocidadMax = 155;     // Máxima en recta
int velocidadMin = 80;     // Mínima en curvas
int umbralCurva = 650;      // Cuando el error supera esto → curva
int umbralRecta = 400;      // Cuando el error es menor → recta
int aceleracion = 1;        // Velocidad con la que sube en rectas

int velocidadActual = 200;  // Arranca lento y se ajusta solo

// --- Motores ---
void motoresAdelante(int velIzq, int velDer) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, velIzq);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, velDer);
}

void motoresParar() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

// --- SETUP ---
void setup() {

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(115200);

  pinMode(LED_ENCENDIDO, OUTPUT);
  pinMode(LED_CALIBRACION, OUTPUT);
  pinMode(BOTON_CALIBRAR, INPUT_PULLUP);

  digitalWrite(LED_ENCENDIDO, HIGH);
  motoresParar();

  // QTR
  qtr.setTypeAnalog();
  qtr.setSensorPins(qtrPins, NUM_SENSORS);

  // Blink
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_CALIBRACION, HIGH);
    delay(200);
    digitalWrite(LED_CALIBRACION, LOW);
    delay(200);
  }

  Serial.println("Robot listo. Mantén presionado el botón 2s para calibrar.");
}

// --- LOOP ---
void loop() {

  static bool botonPrevio = HIGH;
  bool botonActual = digitalRead(BOTON_CALIBRAR);
  static unsigned long tiempoPresionado = 0;
  static bool botonMantenido = false;

  // --- Larga pulsación para calibrar ---
  if (botonPrevio == HIGH && botonActual == LOW) {
    tiempoPresionado = millis();
    botonMantenido = true;
  }

  if (botonMantenido && botonActual == LOW) {

    if (!calibrando && (millis() - tiempoPresionado > 2000)) {

      calibrando = true;
      Serial.println("\n🔧 Calibración iniciada...");
      unsigned long tiempoInicio = millis();
      uint16_t sensorValues[NUM_SENSORS];

      while (millis() - tiempoInicio < 8000) {
        qtr.calibrate();
        qtr.read(sensorValues);

        digitalWrite(LED_CALIBRACION, !digitalRead(LED_CALIBRACION));

        Serial.print("Sensores: ");
        for (int i = 0; i < NUM_SENSORS; i++) {
          Serial.print(sensorValues[i]);
          Serial.print('\t');
        }
        Serial.println();
        delay(100);
      }

      digitalWrite(LED_CALIBRACION, LOW);
      calibrando = false;
      Serial.println("✅ Calibración completa.");
    }
  }

  // --- Pulsación corta Start/Stop ---
  if (botonPrevio == LOW && botonActual == HIGH) {
    botonMantenido = false;

    unsigned long tiempoSoltado = millis() - tiempoPresionado;

    if (!calibrando && tiempoSoltado < 2000) {
      if (!modoSeguir) {
        modoSeguir = true;
        integral = 0;
        lastError = 0;
        Serial.println("▶️ Modo seguir línea activado.");
      } else {
        modoSeguir = false;
        motoresParar();
        Serial.println("⏹️ Modo detenido.");
      }
    }
  }

  botonPrevio = botonActual;

  // --- SEGUIR LÍNEA ---
  if (modoSeguir) {

    uint16_t sensorValues[NUM_SENSORS];
    uint16_t position = qtr.readLineWhite(sensorValues);

    int error = 3500 - position;

    // Integral OFF por estabilidad
    integral = 0;

    // Derivativo filtrado
    static float derivFiltrado = 0;
    float derivRaw = (error - lastError);
    derivFiltrado = 0.7 * derivFiltrado + 0.3 * derivRaw;

    float ajuste =
      (Kp * error) +
      (Kd * derivFiltrado);

    lastError = error;

    // --------------------------
    // CONTROL DE VELOCIDAD DINÁMICA
    // --------------------------

    int absError = abs(error);

    // Si el robot está en curva → BAJA velocidad rápido
    if (absError > umbralCurva) {
      velocidadActual -= 8;
    }
    // Si está en recta → AUMENTA despacio
    else if (absError < umbralRecta) {
      velocidadActual += aceleracion;
    }

    // Limitar velocidad disponible
    velocidadActual = constrain(velocidadActual, velocidadMin, velocidadMax);

    // --------------------------
    // APLICAR VELOCIDAD + PID
    // --------------------------

    int velIzq = velocidadActual + ajuste;
    int velDer = velocidadActual - ajuste;

    velIzq = constrain(velIzq, 0, MAX_PWM);
    velDer = constrain(velDer, 0, MAX_PWM);

    motoresAdelante(velIzq, velDer);
  }
}