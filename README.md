# 🚗 Real-Time Traffic Sign Recognition and Autonomous Vehicle Control System

This project presents a **hybrid AI–embedded system** integrating deep learning-based traffic sign recognition with real-time autonomous vehicle control using Arduino. The system has been successfully validated and published in a **Q1 Scopus-indexed journal (MTAP, Springer)**.

---

## 🧠 Project Overview

This system uses **Convolutional Neural Networks (CNNs)** to detect and classify traffic signs from live camera feeds and automatically adjusts the vehicle's movement using signals sent to an Arduino microcontroller.

It supports:
- Real-time **traffic sign detection**
- Autonomous **speed control and braking**
- **Sensor fusion** using IR and ultrasonic sensors
- **PWM-based motor control** via an L298N H-Bridge

---

## 📂 Repository Structure

```
📁 Car_Model_GTSRB.ipynb        # CNN training using German Traffic Sign Recognition Benchmark
📁 Car_Model_CTSD.ipynb         # CNN training using Chinese Traffic Sign Dataset
📁 Traffic_Sign_Recognition.ipynb # Real-time traffic sign recognition from webcam
📁 model_trained.p              # Pre-trained CNN model (Pickle format)
📁 car_circuit_image.png        # Complete circuit diagram for the vehicle
📁 Line_Following_Obstacle_Avoiding.ino   # Arduino sketch for IR and ultrasonic navigation
📁 Traffic_Sign_Recognition.ino           # Arduino sketch for motor control based on CNN output
📁 Car.pdf                      # Final research paper accepted in MTAP Q1 Journal
📁 requirements.txt             # Python dependency list for environment setup
```

---

## 🔍 Key Features

- 🎯 **99.63% Accuracy on GTSRB**, 99.68% on CTSD
- ⚙️ **Latency**: 24–26ms per inference
- 🧠 CNN Architecture: 4 Conv layers + Dense layers with dropout and batch normalization
- 🎥 Uses **real-time webcam feed** or saved frames for inference
- 🚦 Adaptive control for:
  - Speed Limit Signs (PWM adjustment)
  - Stop/No Entry (hard stop)
  - Children Crossing (speed limit lowering)
- 🔧 Arduino-based control logic synced via serial communication
- 🧪 Comprehensive **testing on simulated road conditions**

---

## 🛠️ Hardware Required

- Arduino UNO R3
- L298N Motor Driver
- 4 × Yellow Gear Motors (DC)
- HC-SR04 Ultrasonic Sensor
- 2 × Infrared Sensors (TCRT5000)
- 1 × Servo Motor (Micro Servo 9G)
- 18650 Li-ion Batteries
- Webcam (e.g., iPhone webcam or USB camera)
- Jumpers, Battery Switch, Breadboard

🔌 See: `car_circuit_image.png` for the complete Fritzing wiring diagram.

---

## 🧪 Dataset Used

1. **GTSRB** – 43 Classes, 34,799 images  
2. **CTSD** – 57 Classes, 6,164 images  

Preprocessing includes:
- Grayscale conversion
- Histogram equalization
- Data augmentation (shear, zoom, rotation, shifts)
- Normalization and reshaping to (32×32×1)

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/nameisashish/Real-time-traffic-sign-recognition-and-autonomous-vehicle-control-system-using-CNN.git
cd traffic-sign-recognition-car
```

### 2. Setup Python Environment

```bash
pip install -r requirements.txt
```

### 3. Run Training or Inference

To train from scratch:
```python
Run Car_Model_GTSRB.ipynb or Car_Model_CTSD.ipynb
```

To run real-time recognition:
```python
Run Traffic_Sign_Recognition.ipynb (ensure webcam and Arduino are connected)
```

---

## 🔄 Arduino Control Logic

- `Traffic_Sign_Recognition.ino`: Processes serial commands from PC and adjusts motor speed or stops.
- `Line_Following_Obstacle_Avoiding.ino`: Uses IR + ultrasonic sensors for path tracking and obstacle handling.

---

## 📊 Results

| Dataset | Accuracy | Test Loss | F1-Score |
|---------|----------|-----------|----------|
| GTSRB   | 99.63%   | 0.0184    | 0.995    |
| CTSD    | 99.68%   | 0.0161    | 1.000    |

---

## 📜 Publication

This project is published in:
> **Multimedia Tools and Applications (MTAP, Springer, Q1 SCI Journal)**  
> _"Real-Time Traffic Sign Recognition and Autonomous Vehicle Control System Using CNN"_  
> [DOI: https://doi.org/10.1007/s11042-025-20853-8]

---

## 📸 Screenshots

- Circuit Diagram

---

## 🤝 Contributors

- **Dr. Girish Kumar N G** (BIT, Bengaluru)
- Ashish Kishore (Research Scholar)
- Aaditya J Krishna (Research Scholar)

---

## 📬 Contact

**Dr. Girish Kumar N G**  
Email: [girishkumarng@bit-bangalore.edu.in](mailto:girishkumarng@bit-bangalore.edu.in)

**Ashish Kishore**  
Email: [ashisha3p@gmail.com](mailto:ashisha3p@gmail.com)

**Aaditya J Krishna**  
Email: [aadityajagadeeshkrishna@gmail.com](mailto:aadityajagadeeshkrishna@gmail.com)
