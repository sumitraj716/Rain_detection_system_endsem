
# 🌧️ Rain Detection System using ESP32

A smart **Rain Detection System** built using the **ESP32 microcontroller**, designed to detect rain and respond with automation using a servo motor and LED indicators. The system includes a **real-time web dashboard** built with HTML, CSS and JavaScript to monitor weather status and control devices remotely.

---

## 🔧 Features

- 🌦️ Real-time rain detection with live status updates
- 📊 Dashboard displaying sensor data using Bootstrap UI
- 💡 LED indicator to signal rain detection
- 🤖 Servo motor automation (e.g., open/close roof/window)
- 🌙 Dark mode for web dashboard
- 🔄 Live ESP32 communication with web interface
- 📈 Data visualization with future scope of logging and cloud storage

---
## 🪢 Wiring / Circuit Connections

| Component        | ESP32 Pin        | Description                      |
|------------------|------------------|----------------------------------|
| Rain Sensor OUT  | D34 (or GPIO34)  | Digital signal from rain sensor |
| Servo Motor      | D18 (or GPIO18)  | PWM control pin for servo       |
| LED Indicator    | D15 (or GPIO15)  | Turns on when rain is detected  |
| VCC (Rain/Servo) | 3.3V / 5V        | Power supply (based on module)  |
| GND              | GND              | Common ground connection        |

🔸 **Note:** Ensure servo motor is powered externally if needed.  
🔸 Use resistors if required for current-limiting LEDs.

---

## 🧰 Technologies Used

- **ESP32** microcontroller (Arduino IDE / PlatformIO)
- **Rain Sensor Module**
- **Servo Motor** & **LEDs**
- **HTML**, **CSS**, **JavaScript**
- **Bootstrap** for responsive UI
- **ESPAsyncWebServer** / WebSerial (if applicable)

---

---

## 🚀 Getting Started

1. **Upload ESP32 Code**  
   Flash the `esp32-code/` to your ESP32 board using Arduino IDE or PlatformIO.

2. **Connect to Wi-Fi**  
   Update your Wi-Fi credentials in the code if required.

3. **Access Web Dashboard**  
   Open the ESP32 IP address in your browser to access the web UI.

4. **Interact Live**  
   Monitor rain status and control the servo or LED directly from your dashboard.

---

---

## 🛠️ Future Improvements

- 🌐 Upload sensor data to Firebase or Google Sheets
- 🧾 Data logging and downloadable reports (CSV/Excel)
- 📱 Mobile-optimized dashboard
- ☁️ Cloud dashboard with remote alerts

---

## 👨‍💻 Author

**Sumit Raj**  
📧 Email: sumit_24a12res716@iitp.ac.in  
🐙 GitHub: [https://github.com/sumitraj716](https://github.com/sumitraj716)

---

## 📜 License

This project is an open source.

