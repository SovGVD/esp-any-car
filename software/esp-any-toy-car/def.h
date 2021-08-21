#ifdef BOARD_ESP32
  // define pins
  #define LEFT_MOTOR1_PIN  27
  #define LEFT_MOTOR2_PIN  26
  #define RIGHT_MOTOR1_PIN 25
  #define RIGHT_MOTOR2_PIN 33
#endif

#ifdef BOARD_ESP32CAM
  // Expected to be CAMERA_MODEL_AI_THINKER
  // https://randomnerdtutorials.com/esp32-cam-car-robot-web-server/
  #define LEFT_MOTOR1_PIN  14
  #define LEFT_MOTOR2_PIN  15
  #define RIGHT_MOTOR1_PIN 13
  #define RIGHT_MOTOR2_PIN 12
#endif

#ifdef BOARD_ESP8266
  // Does not work well with ESP01
  #define LEFT_MOTOR1_PIN  2
  #define LEFT_MOTOR2_PIN  3
  #define RIGHT_MOTOR1_PIN 0
  #define RIGHT_MOTOR2_PIN 1
#endif
