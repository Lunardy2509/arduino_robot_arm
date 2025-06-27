# 🤖 Arduino Robot Arm (3 DoF)

This is a microcontroller project built to control a 3-DoF robotic arm using Arduino.  
The arm can be controlled manually via joystick (HW-504) and supports a **record & playback** feature using a potentiometer.

---

## 📦 Project Overview

- 🔧 **Hardware:** Uses an open-source mechanical design based on [EEZYbotARM MK2](https://www.thingiverse.com/thing:1015238)
- 🎮 **Control:** Joystick HW-504 for manual movement + potentiometer for "record & play"
- 💾 **Logic:** Arduino stores servo positions and replays them on command
- 🔋 **Power Supply:** External 5V for servo stability

---

## 📁 Folder Structure

```bash
arduino_robot_arm/
├── 3D design/              # STL or mechanical files (from open-source EEZYbotARM)
├── circuit schematics/     # Wiring diagrams (Fritzing/PNG)
├── code/                   # Arduino sketch (.ino)
│   └── robot_arm.ino
├── documentation/          # Any additional guides or explanations
└── README.md
```

## 🔌 Components Used
| Component          | Quantity | Notes                                  |
| ------------------ | -------- | -------------------------------------- |
| Arduino Uno        | 1        | Main controller                        |
| Servo Motor (SG90) | 3        | One for each joint                     |
| Joystick Module    | 1        | HW-504 analog joystick                 |
| Potentiometer      | 1        | Switches between manual/playback mode  |
| Push Button        | 1–2      | (Optional) for reset or mode switching |
| Breadboard & Wires | -        | For connection                         |
| 5V Power Supply    | 1        | For powering servos (recommended)      |

## 📚 Arduino Libraries
No external libraries are required. The project uses:
- `Servo.h` → [Included by default in Arduino IDE]
If needed:
```cpp
#include <Servo.h>
```

## 🚀 How to Use
### 1. 🧠 Flash the Code
- Open `code/robot_arm.ino` in Arduino IDE
- Connect your Arduino Uno
- Select the right port and board
- Upload the sketch

### 2. 🔌 Wire Everything
- Refer to `circuit schematics/` for connection diagrams
- Plug in the external 5V power to servo rail (⚠️ avoid using Arduino's 5V pin for servos)

### 3. 🎮 Manual Mode
- Move the joystick to position the robot arm manually
- Positions are controlled in real time

### 4. 💾 Record & Play Mode
- Turn the potentiometer or press a button (depending on your setup)
- Arm enters "record" mode, saves the sequence
- Toggle again to "playback" and repeat the motion

## ⚠️ Disclaimer
I don't own the 3D design for this robot arm. The mechanical design is based on EEZYbotARM MK2. The circuit design and Arduino code are original. If you're looking for alternate robot arm styles, consider exploring more open-source options here.

## 🙌 Credits
- Mechanical Design: EEZYbotARM MK2 by daGHIZmo
- Code & Circuit: @Lunardy2509

## 📬 Contact
- GitHub: @Lunardy2509
- Email: ferdilunardy@gmail.com

---

Let me know if you want:
- Diagram added directly to the README
- Exported PDF of the documentation
- Multi-language README (e.g., Bahasa Indonesia version)  
Happy to assist further!
