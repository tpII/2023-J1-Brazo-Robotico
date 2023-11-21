# Brazo robótico con reconocimiento de objetos en ESP32-Cam

Integrantes:
- Barelli, Clara 
- Demoro, Mauricio
- Madonia, Valentina

## Descripción 🦾
El objetivo principal del proyecto es incorporar la cámara **ESP32-Cam**, reemplazando la placa anterior por la ESP32 y logrando que el usuario pueda ver su transmisión en una interfaz. Además, debe implementarse un **reconocimiento de objetos**, de manera que el usuario pueda seleccionar alguno y hacer que el brazo se acerque a él o lo empuje hacia otro punto del lienzo.

## Tecnologías 💻
- [PlatformIO](https://platformio.org/)
- [Edge Impulse](https://edgeimpulse.com/)
- Nodejs
- C++

## Bitácora 🕰️
| Fecha      | Actividad                                                                                                                                                                                                                                                                  |
|------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 03/09/2023 | Inicio de análisis e investigación de la documentación del proyecto.Comienzo del plan de proyecto.                                                                                                                                                                         |
| 14/09/2023 | Se recibieron: NodeMCU, ESP32-Cam, Fuente de alimentación, Brazo robótico con 4 servos SG-90, Motor stepper y driver, potenciómetro y la plataforma                                                                                                                        |
| 20/09/2023 | Probamos el sistema, funcionó pero con movimientos aleatorios                                                                                                                                                                                                              |
| 22/09/2023 | Investigación para incorporar la cámara ESP32-Cam                                                                                                                                                                                                                          |
| 28/09/2023 | Duda acerca de reconocimiento de imágenes                                                                                                                                                                                                                                  |
| 29/09/2023 | Sospechamos que se quemó la Fuente Multiple Salida Step-down 12v 5v 3.3v Ams1117 Arduino, medimos con voltímetro y no entrega 5V                                                                                                                                           |
| 30/09/2023 | Logramos conectar la Esp32-Cam a Wifi. <br> Tuvimos que modificar la librería <Servo.h> ya que no era compatible con el board Esp32, y hacer algunas modificaciones en el código.                                                                                               |
| 02/10/2023 | Probamos transmisión de cámara con código de documentación de Arduino                                                                                                                                                                                                      |
| 12/10/2023 | Dividimos los temas para investigar acerca del reconocimiento de imágenes                                                                                                                                                                                                  |
| 19/10/2023 | Puesta en común de lo investigado acerca del reconocimiento                                                                                                                                                                                                                |
| 26/10/2023 | Obtuvimos 5 cables macho-hembra de la cátedra para los pines                                                                                                                                                                                                               |
| 27/10/2023 | Prueba para que ESP32-Cam funcione como wifi. Confección de esquema de conexiones con Proteus.                                                                                                                                                                             |
| 30/10/2023 | Creamos la red neuronal utilizando Edge Impulse.                                                                                                                                                                                                                           |
| 31/10/2023 | Entrenamos la red neuronal para distinguir entre un pendrive y dados.                                                                                                                                                                                                      |
| 01/11/2023 | Entrenamos la red neuronal para distinguir un cubo de rubik.                                                                                                                                                                                                               |
| 02/11/2023 | Recibimos 3 cables más macho-hembra.                                                                                                                                                                                                                                       |
| 04/11/2023 | Entrenamos la red neuronal para distinguir un sacapuntas.                                                                                                                                                                                                                  |
| 10/11/2023 | Agregamos más fotos del pendrive para entrenar la red neuronal. <br> Probamos la red neuronal con todos los objetos y tuvimos problemas para reconocerlos.                                                                                                                      |
| 13/11/2023 | Escritura del módulo para el manejo de la cámara.                                                                                                                                                                                                                          |
| 14/11/2023 | Integración del pedido de captura a la cámara al servidor. <br>Se tuvo que reducir la resolución porque el ESP32 se reiniciaba por brownout cuando se capturaba una imagen.                                                                                                    |
| 16/11/2023 | Diseño 3d de soporte para ESP32-Cam.Problemas para integrar la librería de Edge Impulse para reconocimiento de imágenes en C++.                                                                                                                                            |
| 17/11/2023 | Se pudo incorporar el reconocimiento de imágenes en C++.<br>Se creó el endpoint para capturar una imagen con la cámara y devolverla como respuesta.<br>Problemas para guardar y setear la imagen como background del **canvas**.                                                     |
| 20/11/2023 | Fue posible setear la imagen como background del canvas, sin guardarla, falta ampliar su tamaño ya que es de 96x96.<br>Modularizado de detección de objetos.<br>Modificación del punto inicial del brazo robótico (hacia un costado para no interferir con la captura de imágenes)<br> Intentamos conectar la ESP32 al motor, pero este no se movió. |