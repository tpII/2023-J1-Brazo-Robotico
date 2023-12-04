#include <Arduino.h>

#define IN1 12 // Pin IN1 del driver conectado al GPIO16 (D0)
#define IN2 13 // Pin IN2 del driver conectado al GPIO16 (D1)
#define IN3 15 // Pin IN3 del driver conectado al GPIO16 (D2)
#define IN4 14 // Pin IN4 del driver conectado al GPIO16 (D3)
#define SW   3 // Limit switch para calcular posicion inicial

// Límites del ángulo de la base expresados en mediciones del potenciómetro
#define SPR  2048 // Steps per revolution del motor

void BaseMotorSetup();

void BaseMotorUpdate();

void BaseMotorSetAngle(float angle);

void BaseMotorStop();

bool BaseMotorFinished();

void BaseMotorHome();
