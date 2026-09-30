<div align="center">

# 🤖 MEB Robot 1

**Autonomous mobile robot firmware — sensors, motion and embedded control**

![C++](https://img.shields.io/badge/C%2B%2B-Arduino-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Robotics](https://img.shields.io/badge/Robotics-Embedded-111827?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Experimental-f59e0b?style=for-the-badge)

</div>

---

## 🧭 Overview

A focused firmware workspace for the first MEB robot configuration. The repository keeps low-level embedded experiments isolated so motor control, sensor logic and board-specific behavior can be iterated quickly.

## 🧠 Control Model

```text
Sensors
   ↓
Input / Filtering
   ↓
Decision Logic
   ↓
Motor Control
   ↓
Robot Motion
```

The code is intended for hands-on robotics development, where wiring, pin mapping and mechanical constraints are validated together with the firmware.

## 🔧 Core Areas

| Area | Focus |
|---|---|
| Motion | DC motor direction / speed control |
| Sensors | Digital / analog inputs |
| Logic | Rule-based autonomous behavior |
| Hardware | Arduino + driver + motors |
| Testing | Small firmware experiments before integration |

## 🛠️ Stack

**C/C++ · Arduino IDE · Embedded Systems · DC Motors · Sensors · Motor Drivers**

## 🚀 Getting Started

1. Open the relevant `.ino` sketch in Arduino IDE.
2. Select the exact Arduino board and port.
3. Verify pin assignments against the physical wiring.
4. Upload the firmware.
5. Test sensors and motor direction independently before autonomous runs.

> ⚠️ Firmware is hardware-dependent. Treat pin numbers and motor direction assumptions as configuration details, not universal defaults.

## 🚧 Status

**Experimental robotics workspace**

This repository represents an earlier robot configuration; newer MEB work is maintained separately as the hardware evolves.
