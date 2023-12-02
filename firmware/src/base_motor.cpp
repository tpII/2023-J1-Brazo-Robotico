/*
 Step motor turns CCW               Step motor turns CW, 
 Array tab1 used:                  Array tab2 used:
 IN1 IN2 IN3 IN4                   IN1 IN2 IN3 IN4
 1000                              1000
 1100                              1001
 0100                              0001
 0110                              0011
 0010                              0010
 0011                              0110
 0001                              0100
 1001                              1100
*/

#include "base_motor.h"

#define isSet(a,b) (a & b) == b
#define STOP 0
#define TO_CCW 1
#define TO_CW 2

const char CCW[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x09};
const char CW[]  = {0x01, 0x09, 0x08, 0x0c, 0x04, 0x06, 0x02, 0x03};

// --===================== PRIVATE =====================--
String input;
int target = 0;
int actual = 0;
int direction = STOP;

void moveCW(uint timedelay) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(IN1, isSet(CW[i], 1));
        digitalWrite(IN2, isSet(CW[i], 2));
        digitalWrite(IN3, isSet(CW[i], 4));
        digitalWrite(IN4, isSet(CW[i], 8));
        
        actual -= 1;

        delay(timedelay);

        if (actual <= target)
            return;
    }
}

void moveCCW(uint timedelay) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(IN1, isSet(CCW[i], 1));
        digitalWrite(IN2, isSet(CCW[i], 2));
        digitalWrite(IN3, isSet(CCW[i], 4));
        digitalWrite(IN4, isSet(CCW[i], 8));

        actual += 1;

        delay(timedelay);

        if (actual >= target)
            return;
    }
}

// --===================== PUBLIC =====================--

void BaseMotorSetup() {
    pinMode(IN1, OUTPUT); // Set the IN1 pin as OUTPUT
    pinMode(IN2, OUTPUT); // Set the IN2 pin as OUTPUT
    pinMode(IN3, OUTPUT); // Set the IN3 pin as OUTPUT
    pinMode(IN4, OUTPUT); // Set the IN4 pin as OUTPUT
    pinMode(SW, INPUT_PULLUP);
    BaseMotorStop();
}


void BaseMotorUpdate() {
    if (direction == STOP) {
        return;
    } else if (direction == TO_CCW) {
        //uint actual = analogRead(POTE);

        if (actual >= target) {
            direction = STOP;
        } else {
            moveCCW(10);
        }
    } else if (direction == TO_CW) {
        //uint actual = analogRead(POTE);

        if (actual <= target) {
            direction = STOP;
        } else {
            moveCW(10);
        }
    }
    BaseMotorStop();
}

void BaseMotorSetAngle(float angle) {
    // target = 508.35 + 214.51 * angle;
    // target = constrain(target, MIN_POTE, MAX_POTE);

    target = 1024 + 651.9 * angle;
    if (actual < target)
        direction = TO_CCW;
    else if (actual > target)
        direction = TO_CW;
}

void BaseMotorStop() {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
}

bool BaseMotorFinished() {
    return direction == STOP;
}

void BaseMotorHome() {
    //Serial.println("Base Motor Home");
    BaseMotorStop();
    //target = 505;
    //moveTo(505);
    target = 0;

    while (digitalRead(SW) == HIGH) {
        actual = 8;
        moveCW(5);
    }

    actual = 0;

    BaseMotorStop();
}