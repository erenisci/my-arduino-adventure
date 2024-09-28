#include <LiquidCrystal.h>

int GAS_SENSOR = A0;
int LED = 8;
int BUZZER = 9;
int RS = 12, EN = 11, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
LiquidCrystal LCD(RS, EN, D4, D5, D6, D7);

int delayTime = 3000;
int threshold = 300;

int sensor_value = 0;
bool clear_value = false;

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    LCD.begin(16, 2);
}

void loop()
{
    sensor_value = analogRead(GAS_SENSOR);

    if (sensor_value > threshold)
    {
        LCD.setCursor(0, 0);
        LCD.print("   Gas Leak!");
        LCD.setCursor(0, 1);
        LCD.print("   Evacuate!");

        while (analogRead(GAS_SENSOR) > threshold)
        {
            digitalWrite(LED, HIGH);
            digitalWrite(BUZZER, HIGH);
            delay(100);
            digitalWrite(LED, LOW);
            digitalWrite(BUZZER, LOW);
            delay(100);
        }

        LCD.clear();
    }

    delay(delayTime);
}
