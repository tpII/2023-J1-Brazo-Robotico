#include <Arduino.h>

#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>

/* Configuración de la red. */
#define SSID "Schrodinger" // "alumnosInfo"
#define PASSWORD "mauricio1024" // "Informatica2019"
#define MAX_POINTS 512

/**
 * Inicializa el WiFi del ESP8266 con la configuración por defecto
*/
void WiFiSetup();

/**
 * Atiende a los clientes de la red
*/
void WiFiUpdate();