#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int msg[1];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int SW1 = 7;
int flag_click = 0;
int power_led = 3;
int indicator_led = 4;


void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  pinMode(power_led, OUTPUT);
  digitalWrite(power_led, HIGH);
  pinMode(indicator_led, OUTPUT);

  digitalWrite(SW1, HIGH);
}

void loop(void) {
  bool rslt = false;
  int try_count = 0;

  if (digitalRead(SW1) == LOW) {
    if (flag_click == 0) {
      flag_click = 1;
    }
    else if (flag_click == 1) {
      flag_click = 0;

    }

    if (flag_click == 1) {
      msg[0] = 111;
      while (!rslt) {
        Serial.print("try on\n");
        digitalWrite(indicator_led, HIGH);
        rslt = radio.write(msg, 1) || radio.write(msg, 1) || radio.write(msg, 1);
        delay(500);
        digitalWrite(indicator_led, LOW);
        delay(100);
        try_count++;
        Serial.print(try_count);
        if (try_count > 5) {
          break;
        }
      }
      delay(100);
      if (rslt) {
        digitalWrite(indicator_led, HIGH);
        digitalWrite(power_led, HIGH);
      } else {
        digitalWrite(power_led, LOW);
      }
    } else {
      msg[0] = 000;
      while (!rslt) {
        Serial.print("try off\n");
        digitalWrite(indicator_led, LOW);
        rslt = radio.write(msg, 1) || radio.write(msg, 1) || radio.write(msg, 1);
        delay(500);
        digitalWrite(indicator_led, HIGH);
        delay(100);
        try_count++;
        if (try_count > 5) {
          break;
        }
      }
      delay(100);
      if (rslt) {
        digitalWrite(indicator_led, LOW);
        digitalWrite(power_led, HIGH);
      } else {
        digitalWrite(power_led, LOW);
      }
    }
  }
}
