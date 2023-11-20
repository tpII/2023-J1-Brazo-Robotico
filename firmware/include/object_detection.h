#include <Brazo_robotico_con_ESP32-Cam_inferencing.h>
#include <Arduino.h>
#include "edge-impulse-sdk/dsp/image/image.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

#include "esp_camera.h"

// Select camera model - find more camera models in camera_pins.h file here
// https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/Camera/CameraWebServer/camera_pins.h

#define CAMERA_MODEL_AI_THINKER // Has PSRAM

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

/* Constant defines -------------------------------------------------------- */
#define EI_CAMERA_RAW_FRAME_BUFFER_COLS           320
#define EI_CAMERA_RAW_FRAME_BUFFER_ROWS           240
#define EI_CAMERA_FRAME_BYTE_SIZE                 3

/** Retorna un array de hashes con información del objeto detectado y su posición
 * { name: 'NombreObjeto',
 *   x:    'PosX',
 *   y:    'PosY' } 
 */
std::vector<std::unordered_map<std::string, std::string>> captureImage()