#include "wifi_station.h"
#include "base_motor.h"
#include "servos.h"

#include "esp_camera.h"

void setup()
{
    delay(3000);
    Serial.begin(115200);
    Serial.println();

    WiFiSetup();
    BaseMotorSetup();
    ServosSetup();
    BaseMotorHome();
}

void loop()
{
    WiFiUpdate();
}