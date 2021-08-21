//#define BOARD_ESP32
#define BOARD_ESP32CAM
//#define BOARD_ESP8266

// main loop
#define LOOP_TIME 20   // milliseconds

// failsafe
#define FS_WS_THR 20  // 1 second = FS_WS_THR*LOOP_TIME


// Speed
#define MAX_SPEED 250   // max is 255

#define DEBUG

// FOR esp32cam
#define BOARD_ESP32CAM_FRAMESIZE    FRAMESIZE_QVGA
#define BOARD_ESP32CAM_JPEG_QUALITY 20
