#include "wifi_station.h"
#include "base_motor.h"
#include "servos.h"
#include "camera.h"

void setup()
{
    delay(3000);
    // Serial.begin(115200);
    // Serial.println();

    //WiFiSetup();
    //CameraInit();
    //BaseMotorSetup();
    ServosSetup();
    //BaseMotorHome();    
}

void loop()
{
    WiFiUpdate();
}
