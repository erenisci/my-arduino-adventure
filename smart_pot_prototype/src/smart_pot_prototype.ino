#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Sensor pins
#define SOIL_PIN A0
#define WATER_PIN A1
#define TEMP_PIN A2
#define LDR_PIN A3

// Row Y positions
const int ROW1_Y = 4;
const int ROW2_Y = 20;
const int ROW3_Y = 36;
const int ROW4_Y = 52;

// Icons (8x8 bitmaps)
static const unsigned char PROGMEM soilIcon[] = {
  B00000000,
  B00011000,
  B00111100,
  B00100100,
  B00011000,
  B00100100,
  B00100100,
  B00000000
};

static const unsigned char PROGMEM waterIcon[] = {
  B00010000,
  B00011000,
  B00101000,
  B00101000,
  B00101000,
  B00011000,
  B00010000,
  B00000000
};

static const unsigned char PROGMEM tempIcon[] = {
  B00010000,
  B00010000,
  B00010000,
  B00111000,
  B00111000,
  B00111000,
  B00010000,
  B00000000
};

static const unsigned char PROGMEM lightIcon[] = {
  B00101000,
  B00010000,
  B01111100,
  B00111000,
  B01111100,
  B00010000,
  B00101000,
  B00000000
};

// Filter variables
float soilFilt = 0;
float waterFilt = 0;
float lightFilt = 0;
float tempFilt = 0;

// Strong smoothing for LM35
float alphaTemp = 0.05;   // heavy smoothing
float alphaFast  = 0.2;   // for other sensors

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.display();

  soilFilt = analogRead(SOIL_PIN);
  waterFilt = analogRead(WATER_PIN);
  lightFilt = analogRead(LDR_PIN);
  tempFilt = 25;  
}

void loop() {

  int soilRaw  = analogRead(SOIL_PIN);
  int waterRaw = analogRead(WATER_PIN);
  int lightRaw = analogRead(LDR_PIN);
  int tempRaw  = analogRead(TEMP_PIN);

  // LM35 -> Celsius
  float voltage = tempRaw * (5.0 / 1023.0);
  float tempC = voltage * 100.0;

  // Filters
  soilFilt  = soilFilt  * (1 - alphaFast) + soilRaw  * alphaFast;
  waterFilt = waterFilt * (1 - alphaFast) + waterRaw * alphaFast;
  lightFilt = lightFilt * (1 - alphaFast) + lightRaw * alphaFast;
  tempFilt  = tempFilt  * (1 - alphaTemp) + tempC    * alphaTemp;

  // Percent conversions
  int soilPercent = map(constrain((int)soilFilt, 200, 1023), 1023, 200, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  int waterPercent = map((int)waterFilt, 0, 1023, 0, 100);
  waterPercent = constrain(waterPercent, 0, 100);

  int lightPercent = map((int)lightFilt, 0, 1023, 0, 100);
  lightPercent = constrain(lightPercent, 0, 100);

  // Draw
  display.clearDisplay();
  display.setTextSize(1);

  const int ICON_X = 0;
  const int LABEL_X = 12;
  const int VALUE_X = 80;

  // Soil
  display.drawBitmap(ICON_X, ROW1_Y, soilIcon, 8, 8, SSD1306_WHITE);
  display.setCursor(LABEL_X, ROW1_Y);
  display.print("Soil:");
  display.setCursor(VALUE_X, ROW1_Y);
  display.print(soilPercent);
  display.print("%");

  // Water
  display.drawBitmap(ICON_X, ROW2_Y, waterIcon, 8, 8, SSD1306_WHITE);
  display.setCursor(LABEL_X, ROW2_Y);
  display.print("Water:");
  display.setCursor(VALUE_X, ROW2_Y);
  display.print(waterPercent);
  display.print("%");

  // Temperature
  display.drawBitmap(ICON_X, ROW3_Y, tempIcon, 8, 8, SSD1306_WHITE);
  display.setCursor(LABEL_X, ROW3_Y);
  display.print("Temp:");
  display.setCursor(VALUE_X, ROW3_Y);
  display.print(tempFilt, 1);
  display.print("C");

  // Light
  display.drawBitmap(ICON_X, ROW4_Y, lightIcon, 8, 8, SSD1306_WHITE);
  display.setCursor(LABEL_X, ROW4_Y);
  display.print("Light:");
  display.setCursor(VALUE_X, ROW4_Y);
  display.print(lightPercent);
  display.print("%");

  display.display();

  delay(200);
}
