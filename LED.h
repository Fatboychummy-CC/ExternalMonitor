#ifndef __LED__
#define __LED__

#include <Arduino.h>

class LED {
  public:
    explicit LED(byte pinR, byte pinG, byte pinB) {
      R = pinR;
      Serial.println(R);
      G = pinG;
      Serial.println(G);
      B = pinB;
      Serial.println(B);
    };

    void custom(byte valueR, byte valueG, byte valueB) {
      analogWrite(R, valueR);
      analogWrite(G, valueG);
      analogWrite(B, valueB);
    }

    void yellow() {
      digitalWrite(R, true);
      digitalWrite(G, true);
      digitalWrite(B, false);
    }
    void magenta() {
      digitalWrite(R, true);
      digitalWrite(G, false);
      digitalWrite(B, true);
    }

    void cyan() {
      digitalWrite(R, false);
      digitalWrite(G, true);
      digitalWrite(B, true);
    }

    void red() {
      digitalWrite(R, true);
      digitalWrite(G, false);
      digitalWrite(B, false);
    }

    void green() {
      digitalWrite(R, false);
      digitalWrite(G, true);
      digitalWrite(B, false);
    }

    void blue() {
      digitalWrite(R, false);
      digitalWrite(G, false);
      digitalWrite(B, true);
    }

    void white() {
      digitalWrite(R, true);
      digitalWrite(G, true);
      digitalWrite(B, true);
    }

    void off() {
      digitalWrite(R, false);
      digitalWrite(G, false);
      digitalWrite(B, false);
    }

  private:
    byte R, G, B;
};

#endif
