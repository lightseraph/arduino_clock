#include <Arduino.h>
#include <DS3231.h>
#include "MsTimer2.h"

#define ONBOARD_LED 13
#define DATA 5
#define SHIFT 6
#define LATCH 7
#define COLON_CON 9

RTClib myRTC;
// uint8_t digi_seg[7] = {2, 3, 4, 5, 6, 7, 8};
const uint8_t digits[4] = {8, 4, 3, 2};
uint8_t tenDigit = 0;
uint8_t singleDigit = 0;
uint8_t hundredDigit = 0;
uint8_t thousandDigit = 0;
uint8_t number_4bit[4] = {0};

const byte num[10] = {
    0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
const byte bit[4] = {0x80, 0x40, 0x20, 0x10};
const byte colon = 0x1;

/* int num[10][7] = {
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
}; */

void togglePin(uint8_t pin)
{
  digitalWrite(pin, !digitalRead(pin));
}

/* void displayNum(uint8_t number, uint8_t digit)
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
} */

void count()
{
  number_4bit[0]++;
  if (number_4bit[0] > 9)
  {
    number_4bit[0] = 0;
    number_4bit[1]++;
    if (number_4bit[1] > 9)
    {
      number_4bit[1] = 0;
      number_4bit[2]++;
      if (number_4bit[2] > 9)
      {
        number_4bit[2] = 0;
        number_4bit[3]++;
        if (number_4bit[3] > 9)
          number_4bit[3] = 0;
      }
    }
  }
}

void toggleColon()
{
  shiftOut(DATA, SHIFT ,LSBFIRST, colon);
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
}

void dispNum(int number, int digit)
{
  shiftOut(DATA, SHIFT, LSBFIRST, num[number]);

  digitalWrite(LATCH, HIGH);
  // delay(1);
  digitalWrite(LATCH, LOW);
  for (int i = 0; i < 4; i++)
    digitalWrite(digits[i], LOW);
  digitalWrite(digits[digit], HIGH);
}

void disp4Num(uint8_t *number, const uint8_t *digit)
{
  for (int i = 0; i < 4; i++)
  {
    shiftOut(DATA, SHIFT, LSBFIRST, num[number[i]]);
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
    digitalWrite(digits[i], HIGH);
    delay(4);
    digitalWrite(digits[i], LOW);
  }
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(SHIFT, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(COLON_CON, OUTPUT);
  digitalWrite(SHIFT, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(COLON_CON, LOW);
  for (int i = 0; i < 4; i++)
  {
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], LOW);
  }

  MsTimer2::set(100, count);
  MsTimer2::start();
  Serial.begin(115200);
  // attachInterrupt(digitalPinToInterrupt(KEY_A), onKey_APress, LOW);
  /* delay(3000);
  Serial.println(sum); */
  // dispNum(1, 4);
}

void loop()
{
  // put your main code here, to run repeatedly:
  disp4Num(number_4bit, digits);
}