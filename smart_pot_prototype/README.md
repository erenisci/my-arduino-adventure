# Plant Monitoring Prototype

## Project Description

This project is a prototype plant monitoring system designed to measure soil moisture, water level, temperature, and ambient light using basic sensors and an OLED display.  
All sensor values are read through the Arduino and displayed in real time on a 128x64 I2C OLED screen.  
The project is built for prototyping purposes and will later be adapted to an ESP32 for the final smart plant pot system.

## Components Used

- **Arduino UNO** – Main controller for the prototype
- **0.96" I2C OLED Display (SSD1306)** – Displays sensor readings
- **Soil Moisture Sensor (Analog)** – Measures soil moisture level
- **Water Level Sensor (Analog)** – Reads water presence or tank level
- **LM35 Temperature Sensor** – Provides temperature in °C
- **LDR (Light-Dependent Resistor)** – Measures ambient light level
- **10kΩ Resistor** – Used with the LDR voltage divider
- **Breadboard & Jumper Wires** – For prototyping connections

## Circuit Connections

Below is a detailed explanation of the circuit connections for the plant monitoring system.

### OLED Display (I2C)

- VCC → 5V
- GND → GND
- SDA → A4
- SCL → A5

### Soil Moisture Sensor

- A0 → A0
- VCC → 5V
- GND → GND

### Water Level Sensor

- A0 → A1
- VCC → 5V
- GND → GND

### LM35 Temperature Sensor

- Vout → A2
- VCC → 5V
- GND → GND

### LDR (Light Sensor)

Voltage divider setup:

- LDR one leg → 5V
- LDR other leg → A3
- 10kΩ resistor from A3 → GND

## Code Explanation

The code continuously reads analog inputs from all sensors and processes the values.  
To stabilize noisy readings (especially the LM35 temperature sensor and LDR), an **Exponential Moving Average (EMA) filter** is applied to each measurement.  
The OLED screen shows the filtered values with icons for each category. ([Source Code](src/smart_pot_prototype.ino))

### Main Code Logic:

- Read raw analog values from the sensors
- Convert the LM35 reading into Celsius
- Apply EMA filtering for stable output
- Convert soil, water, and light sensor values into percentages (0–100%)
- Display all data on the OLED in four rows with small icons
- Refresh every 200 ms

## How to Use

1. Assemble the circuit using a breadboard according to the connections above.
2. Upload the provided code via Arduino IDE.
3. Power the Arduino — the OLED screen will immediately show sensor readings.
4. Adjust and test the sensors by touching soil, exposing the LDR to light, or dipping the water sensor.
5. This prototype will later be migrated to an ESP32 for the final smart plant pot system.
