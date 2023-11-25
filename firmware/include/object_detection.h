#ifndef OBJECT_DETECTION_H
#define OBJECT_DETECTION_H

#include <iostream>
#include <unordered_map>
#include <vector>

/** Retorna un array de hashes con información del objeto detectado y su posición
 * { name: 'NombreObjeto',
 *   x:    'PosX',
 *   y:    'PosY' } 
 */
std::vector<std::unordered_map<std::string, std::string>> CaptureImage();
void ObjectDetectionSetup();
#endif