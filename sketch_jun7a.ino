#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Common I2C address: 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensorPin = A0;
const int relayPin = 8;

const int Good_Quality = 200;
const int Polluted_Air = 1023;

void setup()
{
  pinMode(relayPin, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Oxygen System");
  delay(2000);
  lcd.clear();
}

void loop()
{
  int sensorValue = analogRead(sensorPin);

  int oxygen = map(sensorValue,
                   Good_Quality,
                   Polluted_Air,
                   0,
                   100);

  oxygen = constrain(oxygen, 0, 100);

  lcd.clear();

  if (oxygen > 21)
  {
    digitalWrite(relayPin, LOW); // Fan OFF

    lcd.setCursor(0, 0);
    lcd.print("Fan: OFF");

    lcd.setCursor(0, 1);
    lcd.print("Oxy:");
    lcd.print(oxygen);
    lcd.print("%");
  }
  else if (oxygen < 5)
  {
    digitalWrite(relayPin, HIGH); // Fan ON

    lcd.setCursor(0, 0);
    lcd.print("Fan: ON");

    lcd.setCursor(0, 1);
    lcd.print("Oxy:");
    lcd.print(oxygen);
    lcd.print("%");
  }
  else
  {
    digitalWrite(relayPin, LOW);

    lcd.setCursor(0, 0);
    lcd.print("Oxy Normal");

    lcd.setCursor(0, 1);
    lcd.print("Oxy:");
    lcd.print(oxygen);
    lcd.print("%");
  }

  Serial.print("Sensor = ");
  Serial.print(sensorValue);
  Serial.print("  Oxygen = ");
  Serial.print(oxygen);
  Serial.println("%");

  delay(1000);
}