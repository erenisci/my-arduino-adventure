# Gas Leak Detection System

## Project Description

This project uses a gas sensor to detect gas leaks. When the sensor value exceeds a predefined threshold, a buzzer sounds, and an LED blinks. Simultaneously, a 16x2 LCD display shows a warning message indicating the gas leak and the need to evacuate.

## Components Used

- **Gas Sensor (e.g., MQ-2, MQ-5)** - To detect the presence of gas.
- **Buzzer** - To provide an audible alarm when gas is detected.
- **LED** - To visually indicate the gas leak by blinking.
- **16x2 LCD Display** - To display a warning message when the gas leak is detected.
- **Arduino UNO** - For controlling the components.

## Circuit Connections

- Gas Sensor:

  - Analog Output (A0) → A0 pin on Arduino
  - VCC → 5V
  - GND → GND

- Buzzer:

  - Positive → Pin 9
  - Negative → GND

- LED:

  - Anode (+) → Pin 8 (through a 330Ω resistor)
  - Cathode (-) → GND

- 16x2 LCD:

  - RS → Pin 12
  - EN → Pin 11
  - D4 → Pin 4
  - D5 → Pin 5
  - D6 → Pin 6
  - D7 → Pin 7
  - VCC → 5V
  - GND → GND

## Code Explanation

The code reads values from the gas sensor using analogRead(). If the sensor value exceeds the defined threshold (300 in this case), the buzzer is activated, the LED starts blinking, and the LCD screen displays a gas leak warning. The loop continuously checks the gas sensor value, and if it's above the threshold, the alarm system stays active until the gas level drops below the threshold.

### Main Code Logic:

- The gas sensor reads the surrounding gas levels.
- If the gas level surpasses the threshold, the buzzer and LED are activated.
- The LCD shows two lines of text: "Gas Leak!" and "Evacuate!".
- The LED and buzzer blink and sound at a regular interval until the gas level drops back below the threshold.
- The system waits for 3 seconds (delayTime) before checking again.
- [Source Code](src/gas_sensor.ino)

## How to Use

- Assemble the circuit according to the connections provided above.
- Upload the code to your Arduino using the Arduino IDE.
- Power the system, and it will continuously monitor the gas levels.
- If a gas leak is detected, the system will provide both a visual and audible alert, and the LCD will display a warning message.
- Once the gas level drops below the threshold, the alert system will stop.
