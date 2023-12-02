#include <Arduino.h>

#define IN1 16 // Pin IN1 del driver conectado al GPIO16 (D0)
#define IN2  0 // Pin IN2 del driver conectado al GPIO16 (D1)
#define IN3  3 // Pin IN3 del driver conectado al GPIO16 (D2)
#define IN4  1 // Pin IN4 del driver conectado al GPIO16 (D3)
#define SW   2 // Limit switch para calcular posicion inicial

// Límites del ángulo de la base expresados en mediciones del potenciómetro
#define SPR  2048 // Steps per revolution del motor

void BaseMotorSetup();

void BaseMotorUpdate();

void BaseMotorSetAngle(float angle);

void BaseMotorStop();

bool BaseMotorFinished();

void BaseMotorHome();