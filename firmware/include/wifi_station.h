#include <Arduino.h>

#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>

/* Configuración de la red. */
#define SSID "Brazo_Robotico" // "alumnosInfo"
#define PASSWORD "12345678" // "Informatica2019"
#define MAX_POINTS 512

/**
 * Inicializa el WiFi del ESP8266 con la configuración por defecto
*/
void WiFiSetup();

/**
 * Atiende a los clientes de la red
*/
void WiFiUpdate();
