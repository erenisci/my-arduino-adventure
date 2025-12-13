# Smart Pot Prototype

## Project Description

Smart Pot Prototype is a sensor-based plant monitoring system built to measure soil moisture, water level, temperature, and ambient light.  
The prototype uses an Arduino UNO and displays all sensor data in real time on a 128x64 SSD1306 OLED screen.  
This repository represents the **prototyping phase**, which will later be migrated to an ESP32 for the final smart plant pot design.

## Components Used

- **Arduino UNO** – Microcontroller for the prototype
- **0.96" I2C OLED Display (SSD1306)** – Visual output for all readings
- **Soil Moisture Sensor (Analog)** – Soil hydration measurement
- **Water Level Sensor (Analog)** – Tank or presence detection
- **LM35 Temperature Sensor** – Accurate temperature readings in °C
- **LDR (Light-Dependent Resistor)** – Ambient light detection
- **10kΩ Resistor** – Required for the LDR voltage divider
- **Breadboard & Jumper Wires** – For prototyping and testing

## Circuit Connections

### OLED Display (SSD1306, I2C)

- VCC → 5V
- GND → GND
- SDA → A4
- SCL → A5

### Soil Moisture Sensor

- Signal → A0
- VCC → 5V
- GND → GND

### Water Level Sensor

- Signal → A1
- VCC → 5V
- GND → GND

### LM35 Temperature Sensor

- Vout → A2
- VCC → 5V
- GND → GND

### LDR (Light Sensor) with Voltage Divider

- LDR leg → 5V
- Other LDR leg → A3
- 10kΩ resistor from A3 → GND

## Code Explanation

The system continuously reads analog values from all sensors and applies **Exponential Moving Average (EMA)** filtering for smoother readings.  
Soil, water, and light values are mapped to percentage scales (0–100%), while the temperature is calculated in °C.
The OLED displays each value with its corresponding icon in four aligned rows. ([Source Code](src/smart_pot_prototype.ino))

### Main Features:

- Real-time multi-sensor monitoring
- Filtered and stable readings
- Clean icon-based OLED display
- Modular design for an easy future transition to ESP32

## How to Use

1. Build the circuit on a breadboard following the pin mappings.
2. Upload the provided code using Arduino IDE.
3. Power the system — the OLED will begin showing live sensor data.
4. Test sensor behavior (soil moisture, water contact, light changes).
5. This prototype will eventually evolve into a full **Smart Pot** ESP32-based final product.
