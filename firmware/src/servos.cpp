#include "servos.h"

// --===================== PRIVATE =====================--

Servo servoQ2, servoQ3;
int s_target[] = {1341, 1075};
int s_actual[] = {0, 0};
int s_delay[] = {0, 0};
int s_delayCount[] = {0, 0};
int servos_finish = 2;

void moveTo(int servoN, int pos) {
    if (pos < 250 || pos > 2000)
        return; // Safety

    Servo *servo = servoN == 2 ? &servoQ2
                               : &servoQ3;

    int actual = s_actual[servoN - 2];

    if (actual == pos)
        return;

    if (actual < pos) {
        // Tengo que girar en sentido antihorario hasta la posición

        while (actual < pos) {
            actual += STEP;
            s_actual[servoN - 2] = actual;
            servo->writeMicroseconds(actual);
            delay(STEP_DELAY);
        }
    } else {
        // Tengo que girar en sentido horario hasta la posición
        while (actual > pos) {
            actual -= STEP;
            s_actual[servoN - 2] = actual;
            servo->writeMicroseconds(actual);
            delay(STEP_DELAY);
        }
    }

    s_actual[servoN - 2] = pos;
    servo->writeMicroseconds(pos);
}

/**
 * Mueve el servo 1us hacia su posición final.
 * Retorna 1 si llegó al objetivo
 */
int updateServo(int servoN, int t) {
    Servo *servo = servoN == 2 ? &servoQ2
                               : &servoQ3;

    int actual = s_actual[servoN - 2];

    if (actual == t)
        return 1;

    actual += (actual < t) - (actual > t); // if actual < t actual++ else if actual > t actual--
    s_actual[servoN - 2] = actual;
    servo->writeMicroseconds(actual);
    return 0;
}

void setDelays() {
    float dif2 = abs(s_target[0] - s_actual[0]),
          dif3 = abs(s_target[1] - s_actual[1]);

    float dif = max(dif2, dif3);

    s_delay[0] = dif2 ? floor(dif / dif2) : 0;
    s_delay[1] = dif3 ? floor(dif / dif3) : 0;
    // s_delay[2] = dif4 ? floor(dif / dif4) : 0;
    // s_delay[3] = dif5 ? floor(dif / dif5) : 0;

    s_delayCount[0] = s_delay[0];
    s_delayCount[1] = s_delay[1];
    // s_delayCount[2] = s_delay[2];
    // s_delayCount[3] = s_delay[3];
}

// --===================== PUBLIC =====================--

void ServosSetup() {
    //ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    servoQ2.setPeriodHertz(50);
    servoQ3.setPeriodHertz(50);

    servoQ2.attach(Q2, 300, 2000); //887
    servoQ3.attach(Q3, 300, 2000); //1490
    //servoQ4.attach(Q4, 300, 2000, 1938); //1985
    //delay(500);
    // servoQ5.attach(Q5, 300, 2000, 1150);
    // delay(500);
    ServosHome();
}

void ServosHome() {
    servoQ2.writeMicroseconds(1341);
    s_actual[0] = 1009;
    servoQ3.writeMicroseconds(1075);
    s_actual[1] = 1100;
    //moveTo(&servoQ2, 1009);
    //moveTo(&servoQ3, 1100);
    //moveTo(&servoQ4, 1938);
    //moveTo(&servoQ5, 1150);
}

void ServosUpdate() {
    // Mueve los servos hasta el objetivo
    if (servos_finish == 2)
        return;

    servos_finish = 0;
    if (s_delayCount[0]-- == 0) {
        servos_finish += updateServo(2, s_target[0]);
        s_delayCount[0] = s_delay[0];
    }
    if (s_delayCount[1]-- == 0) {
        servos_finish += updateServo(3, s_target[1]);
        s_delayCount[1] = s_delay[1];
    }
    // if (s_delayCount[2]-- == 0) {
    //     servos_finish += updateServo(&servoQ4, s_target[2]);
    //     s_delayCount[2] = s_delay[2];
    // }
    /*if (s_delayCount[3]-- == 0) {
        servos_finish += updateServo(&servoQ5, s_target[3]);
        s_delayCount[3] = s_delay[3];
    }*/
    float q2 = (1756.4 - s_actual[0] / 609.9);
    float q3 = (1002.9 - s_actual[1] / 411.3);
    // float q4 = (1029.9 - servoQ4.readMicroseconds()) / 651.1;
    //servoQ5.writeMicroseconds(constrain(1020.7 - 603.8 * (-PI * .5 - q2 - q3 - q4), 300, 2000));
}

void ServosSetAngles(float q2, float q3, float q4, float q5) {
    s_target[0] = constrain(1756.4 - 609.9 * q2, 300, 2000);
    s_target[1] = constrain(1002.9 - 411.3 * q3, 300, 2000);
    //s_target[2] = constrain(308.73 - 592.40 * q4, 300, 2000);
    //s_target[2] = constrain(1029.9 - 651.1 * q4, 300, 2000);
    //s_target[3] = constrain(1020.7 - 603.8 * q5, 300, 2000);

    setDelays();

    servos_finish = 0;
}

bool ServosFinished() {
    return servos_finish == 2;
}

void ServosMove(int servo, int d) {
    Servo *s = servo == 2 ? &servoQ2
                          : &servoQ3;
            //  : servo == 4 ? &servoQ4
            //               : &servoQ5;

    s_actual[servo - 2] += d;
    s->writeMicroseconds(s_actual[servo - 2]);
    //Serial.println("S" + String(servo) + ":" + String(s->readMicroseconds()));
}
