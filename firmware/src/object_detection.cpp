#include "object_detection.h"
#include <Brazo_robotico_con_ESP32-Cam_inferencing.h>
#include "edge-impulse-sdk/dsp/image/image.hpp"
#include <Arduino.h>

#include "camera.h"
#include "esp_camera.h"

/* Constant defines -------------------------------------------------------- */
#define EI_CAMERA_RAW_FRAME_BUFFER_COLS           320
#define EI_CAMERA_RAW_FRAME_BUFFER_ROWS           240
#define EI_CAMERA_FRAME_BYTE_SIZE                 3

/* Private variables ------------------------------------------------------- */
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal
uint8_t *snapshot_buf; //points to the output of the capture
static std::vector<std::unordered_map<std::string, std::string>> detectedObjects;

/* Function definitions ------------------------------------------------------- */

static int ei_camera_get_data(size_t offset, size_t length, float *out_ptr) {
    // we already have a RGB888 buffer, so recalculate offset into pixel index
    size_t pixel_ix = offset * 3;
    size_t pixels_left = length;
    size_t out_ptr_ix = 0;

    while (pixels_left != 0) {
        out_ptr[out_ptr_ix] = (snapshot_buf[pixel_ix] << 16) + (snapshot_buf[pixel_ix + 1] << 8) + snapshot_buf[pixel_ix + 2];

        // go to the next pixel
        out_ptr_ix++;
        pixel_ix+=3;
        pixels_left--;
    }
    // and done!
    return 0;
}

void DetectObjects(uint8_t *fb_buf, size_t fb_len) {
    detectedObjects.clear();

    // instead of wait_ms, we'll wait on the signal, this allows threads to cancel us...
    if (ei_sleep(5) != EI_IMPULSE_OK) {
        return;
    }

    snapshot_buf = (uint8_t*)malloc(EI_CAMERA_RAW_FRAME_BUFFER_COLS * EI_CAMERA_RAW_FRAME_BUFFER_ROWS * EI_CAMERA_FRAME_BYTE_SIZE);

    // check if allocation was successful
    std::unordered_map<std::string, std::string> hash;
    if(snapshot_buf == nullptr) {
        hash["error"] = "ERR: Failed to allocate snapshot buffer!";
        detectedObjects.push_back(hash);
        ei_printf("ERR: Failed to allocate snapshot buffer!\n");
        return;
    }

    ei::signal_t signal;
    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
    signal.get_data = &ei_camera_get_data;

    bool converted = fmt2rgb888(fb_buf, fb_len, PIXFORMAT_JPEG, snapshot_buf);
    if(!converted){
      ei_printf("Conversion failed\n");
      free(snapshot_buf);
      return;
    }

    ei::image::processing::crop_and_interpolate_rgb888(
      snapshot_buf,
      EI_CAMERA_RAW_FRAME_BUFFER_COLS,
      EI_CAMERA_RAW_FRAME_BUFFER_ROWS,
      snapshot_buf,
      EI_CLASSIFIER_INPUT_WIDTH,
      EI_CLASSIFIER_INPUT_HEIGHT);

    // Run the classifier
    ei_impulse_result_t result = { 0 };

    EI_IMPULSE_ERROR err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK) {
        hash["error"] = "Failed to capture image";
        detectedObjects.push_back(hash);
        ei_printf("ERR: Failed to run classifier (%d)\n", err);
        free(snapshot_buf);
        return;
    }

    // print the predictions
    ei_printf("Predictions (DSP: %d ms., Classification: %d ms., Anomaly: %d ms.): \n",
                result.timing.dsp, result.timing.classification, result.timing.anomaly);
  #if EI_CLASSIFIER_OBJECT_DETECTION == 1        
      bool bb_found = result.bounding_boxes[0].value > 0;
      for (size_t ix = 0; ix < result.bounding_boxes_count; ix++) {
          auto bb = result.bounding_boxes[ix];
          if (bb.value == 0) {
              continue;
          }        
          // Define the object and its coordinates
          hash["object"] = bb.label;
          hash["x"] = std::to_string(bb.x);
          hash["y"] = std::to_string(bb.y);
          // Add the hash to the array
          detectedObjects.push_back(hash);
          ei_printf("    %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\n", bb.label, bb.value, bb.x, bb.y, bb.width, bb.height);
      }
      if (!bb_found) {
          hash["error"] = "No objects found\n";
          detectedObjects.push_back(hash);
          ei_printf("    No objects found\n");
      }
      free(snapshot_buf);
      return;
  #endif
}

std::vector<std::unordered_map<std::string, std::string>> GetDetectedObjects(){
  return detectedObjects;
}


#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_CAMERA
#error "Invalid model for current sensor"
#endif
