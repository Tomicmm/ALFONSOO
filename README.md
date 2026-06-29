<div align="center">

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&weight=700&size=28&pause=1000&color=58A6FF&center=true&vCenter=true&width=600&lines=🤖+ALFONSOO;Line+Following+Robot;LNR+Competition+2025;ESP32+%7C+PID+Control+%7C+3D+Printed" alt="Typing SVG" />

<br/>

![Status](https://img.shields.io/badge/Status-En%20desarrollo-yellow?style=for-the-badge)
![Competition](https://img.shields.io/badge/Competencia-LNR%20Argentina-blue?style=for-the-badge)
![MCU](https://img.shields.io/badge/MCU-ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![License](https://img.shields.io/badge/Licencia-MIT-green?style=for-the-badge)

<br/>

```
╔══════════════════════════════════════════════════════╗
║        🏁  ALFONSOO — Robot Seguidor de Línea  🏁    ║
║         Competencia LNR Argentina · ESP32 · PID      ║
╚══════════════════════════════════════════════════════╝
```

</div>

---

## 📌 Descripción / Description

<img align="right" width="180" src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExaXZsanN3ZWtieXB4a3N5Y2JlNWU0ZmJxeGN5OHViMXUwZ3NkZnBoNiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/26tn33aiTi1jkl6H6/giphy.gif"/>

**ES** — ALFONSOO es un robot autónomo seguidor de línea diseñado y construido para competir en la **Liga Nacional de Robótica (LNR)**. El proyecto abarca diseño electrónico, programación con control PID y chasis impreso en 3D.

**EN** — ALFONSOO is an autonomous line-following robot designed and built to compete in the **Liga Nacional de Robótica (LNR)**. The project covers electronic design, PID control programming, and a fully 3D-printed chassis.

<br clear="right"/>

---

## ⚡ Tech Stack

<div align="center">

![C++](https://img.shields.io/badge/C++-004482?style=for-the-badge&logo=cplusplus&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino%20IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Fusion 360](https://img.shields.io/badge/Fusion%20360-FF6600?style=for-the-badge&logo=autodesk&logoColor=white)

</div>

---

## 📂 Estructura del Repositorio / Repo Structure

```
📦 ALFONSOO
 ┣ 🔧 HARDWARE
 ┃   ┣ Esquemas de conexión
 ┃   ┣ Lista de componentes (BOM)
 ┃   └── PCB / Pinout ESP32
 ┃
 ┣ 💻 SOFTWARE
 ┃   ┣ main.cpp (loop principal)
 ┃   ┣ pid.cpp (control PID)
 ┃   └── config.h (parámetros Kp · Ki · Kd)
 ┃
 ┣ 🖨️ CHASIS 3D
 ┃   ┣ Archivos .STL
 ┃   ┣ Archivos .F3D / .STEP
 ┃   └── Fotos del chasis
 ┃
 ┗ 📚 LIBRERIAS
     └── Dependencias del proyecto
```

---

## 🧠 Control PID

<div align="center">

| Parámetro | Descripción | Efecto |
|-----------|-------------|--------|
| **Kp** | Proporcional | Respuesta inmediata al error |
| **Ki** | Integral | Corrección de error acumulado |
| **Kd** | Derivativo | Suaviza oscilaciones |

```
Error = Setpoint - Posición sensores IR
Output = Kp·e + Ki·∫e·dt + Kd·(de/dt)
```

</div>

---

## 👨‍💻 Equipo / Team

<div align="center">

| 👤 | Nombre | Rol |
|----|--------|-----|
| 🔩 | **Tomás Colicchia** | Hardware & Ensamble |
| 🖨️ | **Santiago Avalos** | Chasis 3D & Diseño |
| ⚡ | **Dante Bollo** |  Electrónica & Programación |

</div>

---

## 📊 Estado del Proyecto / Project Status

<div align="center">

| Módulo | Estado |
|--------|--------|
| 🔧 Hardware | ![](https://img.shields.io/badge/-En%20progreso-yellow) |
| 💻 Software PID | ![](https://img.shields.io/badge/-En%20progreso-yellow) |
| 🖨️ Chasis 3D | ![](https://img.shields.io/badge/-En%20progreso-yellow) |
| 🏁 Competencia LNR | ![](https://img.shields.io/badge/-Próximamente-blue) |

</div>

---

<div align="center">

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=14&pause=2000&color=58A6FF&center=true&vCenter=true&width=500&lines=Construido+con+circuitos%2C+código+y+café+☕;Built+with+circuits%2C+code+and+coffee+☕" alt="footer" />

[![GitHub](https://img.shields.io/badge/GitHub-Tomicmm-181717?style=flat-square&logo=github)](https://github.com/Tomicmm)

</div>
