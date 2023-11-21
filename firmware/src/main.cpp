#include "wifi_station.h"
#include "base_motor.h"
#include "servos.h"
#include "object_detection.h"
#include "camera.h"

void setup()
{
    delay(3000);
    Serial.begin(115200);
    Serial.println();

    WiFiSetup();
    CameraInit();
    ObjectDetectionSetup();
    BaseMotorSetup();
    ServosSetup();
    BaseMotorHome();    
}

void loop()
{
    WiFiUpdate();
}
