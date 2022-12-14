#include <Arduino.h>
#include <DS3231.h>

#define ONBOARD_LED 13
#define KEY_A 2
#define KEY_B 3

RTClib myRTC;

void togglePin(uint8_t pin)
{
  digitalWrite(pin, !digitalRead(pin));
}

void onKey_APress()
{
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(KEY_A, INPUT_PULLUP);
  pinMode(KEY_B, INPUT_PULLUP);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(KEY_A), onKey_APress, LOW);
}

void loop()
{
  // put your main code here, to run repeatedly:
  togglePin(ONBOARD_LED);
  delay(500);
}