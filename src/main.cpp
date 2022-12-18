#include <Arduino.h>
#include <DS3231.h>
#include "MsTimer2.h"

#define ONBOARD_LED 13
#define KEY_A 2
#define KEY_B 3
#define SEG_C 4

RTClib myRTC;
uint8_t digi_seg[7] = {2, 3, 4, 5, 6, 7, 8};
uint8_t digits[2] = {9, 10};
int tenDigit = 0;
int singleDigit = 0;

int num[10][7] = {
    {0, 0, 0, 0, 0, 0, 1}, // 数字0
    {1, 0, 0, 1, 1, 1, 1}, // 数字1
    {0, 0, 1, 0, 0, 1, 0}, // 数字2
    {0, 0, 0, 0, 1, 1, 0}, // 数字3
    {1, 0, 0, 1, 1, 0, 0}, // 数字4
    {0, 1, 0, 0, 1, 0, 0}, // 数字5
    {0, 1, 0, 0, 0, 0, 0}, // 数字6
    {0, 0, 0, 1, 1, 1, 1}, // 数字7
    {0, 0, 0, 0, 0, 0, 0}, // 数字8
    {0, 0, 0, 0, 1, 0, 0}, // 数字9
};

void togglePin(uint8_t pin)
{
  digitalWrite(pin, !digitalRead(pin));
}

void displayNum(uint8_t number, uint8_t digit)
{
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(digi_seg[i], num[number][i]);
  }
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(digits[i], LOW);
  }
  digitalWrite(digits[digit], HIGH);
  delay(10);
}

void count()
{
  singleDigit++;
  if (singleDigit > 9)
  {
    singleDigit = 0;
    tenDigit++;
  }
  if (tenDigit > 9)
    tenDigit = 0;
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(ONBOARD_LED, OUTPUT);
  for (int i = 0; i < 7; i++)
  {
    pinMode(digi_seg[i], OUTPUT);
    digitalWrite(digi_seg[i], HIGH);
  }

  for (int i = 0; i < 2; i++)
  {
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], LOW);
  }
  MsTimer2::set(1000, count);
  MsTimer2::start();
  Serial.begin(115200);
  // attachInterrupt(digitalPinToInterrupt(KEY_A), onKey_APress, LOW);
  /* delay(3000);
  Serial.println(sum); */
}

void loop()
{
  // put your main code here, to run repeatedly:

  displayNum(singleDigit, 1);

  displayNum(tenDigit, 0);
}