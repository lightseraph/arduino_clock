#include <Arduino.h>
#include <DS3231.h>

#define ONBOARD_LED 13
#define KEY_A 2
#define KEY_B 3
#define SEG_C 4

RTClib myRTC;
uint8_t digi_seg[7] = {2, 3, 4, 5, 6, 7, 8};
int count = 0;

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

int calc(int a, int b, int c)
{
  return a + b - c;
}

void onKey_APress()
{
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
  Serial.begin(115200);
  // attachInterrupt(digitalPinToInterrupt(KEY_A), onKey_APress, LOW);
  /* delay(3000);
  int a = 89;
  int b = 18;
  int c = 21;
  int sum = calc(a, b, c);
  Serial.println(sum); */
}

void loop()
{
  // put your main code here, to run repeatedly:

  /* for (int i = 0; i < 7; i++)
  {
    togglePin(digi_seg[i]);
    delay(500);
  } */

  for (int j = 0; j < 10; j++)
  {
    for (int i = 0; i < 7; i++)
    {
      digitalWrite(digi_seg[i], num[j][i]);
    }
    delay(1000);
  }
}
