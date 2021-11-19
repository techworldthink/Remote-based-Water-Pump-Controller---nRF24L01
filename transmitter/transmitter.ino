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
  bool rslt;

  if (digitalRead(SW1) == LOW) {
    if (flag_click == 0) {
      flag_click = 1;
    }
    else if (flag_click == 1) {
      flag_click = 0;

    }

    if (flag_click == 1) {
      msg[0] = 111;
      rslt = radio.write(msg, 1);
      rslt = radio.write(msg, 1);
      rslt = radio.write(msg, 1);
      delay(100);
      if (rslt) {
        digitalWrite(indicator_led, HIGH);
      }
      //else {
      //  digitalWrite(indicator_led, LOW);
      // }
    } else {
      msg[0] = 000;
      rslt = radio.write(msg, 1);
      rslt = radio.write(msg, 1);
      rslt = radio.write(msg, 1);
      delay(100);
      if (rslt) {
        digitalWrite(indicator_led, LOW);
      }
      //else {
      // digitalWrite(indicator_led, HIGH);
      //}
    }
  }
}
