#include "config.h"
#include "def.h"

#ifdef BOARD_ESP32CAM
  #include "esp_camera.h"
  #include "camera.h"
  camera_fb_t * fb = NULL;
#endif


#if defined(BOARD_ESP32) || defined(BOARD_ESP32CAM)
  #include "soc/soc.h"           // Disable brownour problems
  #include "soc/rtc_cntl_reg.h"  // Disable brownour problems
  //#include <analogWrite.h>  // Looks like this in coflict with BOARD_ESP32CAM
#endif

#include "config_wifi.h"

#ifdef BOARD_ESP8266
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif

#ifdef defined(BOARD_ESP32) || defined(BOARD_ESP32CAM)
  #include "WiFi.h"
#endif

#include "ESPAsyncWebServer.h"
#include "web/index.html.gz.h"

unsigned long currentTime;
unsigned long previousTime;
unsigned long loopTime;

// define move params
float speed     = 0;
float yaw       = 0;
float speedCalc = 0;
float yawCalc   = 0;

// define motor values
float leftMotor = 0;
float rightMotor = 0;

// Failsafe
bool FS_FAIL = false;
uint8_t FS_WS_count = 0;

// Is rover upsidedown
bool enabled = true;

// WiFi
// WebServer
bool clientOnline = false;
AsyncWebSocketClient * wsclient;
IPAddress WiFiIP;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup() {
  #if defined(BOARD_ESP32) || defined(BOARD_ESP32CAM)
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  #endif

  #ifdef BOARD_ESP32CAM
    cameraSetup();
  #endif

  #ifdef DEBUG
    Serial.begin(115200);
    Serial.println("debug mode");
  #endif
  // init WiFi access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_ssid, AP_pass);
  WiFiIP = WiFi.softAPIP();

  initWebServer();
}

void loop() {
  currentTime = millis();
  if (currentTime - previousTime >= LOOP_TIME) {
    previousTime = currentTime;
    updateFailsafe();
    calcMove();
    doMove();
    FS_WS_count++;

    loopTime = millis() - currentTime;
  }

  #ifdef BOARD_ESP32CAM
    cameraHandleStream();
  #endif
}

void calcMove()
{  
  if (speed > 0) {
    leftMotor  = speed;
    rightMotor = speed;
  } else if (speed < 0) {
    leftMotor  = -speed;
    rightMotor = -speed;
  } else {
    leftMotor  = 0;
    rightMotor = 0;
  }

  if (abs(yaw) > abs(speed)) yaw = speed;

  if (yaw > 0.1) {
    rightMotor = rightMotor + (speed > 0 ? -yaw : yaw);
  } else if (yaw < -0.1){
    leftMotor  = leftMotor  + (speed > 0 ? -yaw : yaw);
  }
}

void doMove()
{
//  analogWrite(LEFT_MOTOR1_PIN,   leftMotor > 0 ? leftMotor*MAX_SPEED  : 0);
//  analogWrite(LEFT_MOTOR2_PIN,   leftMotor > 0 ? 0                    : leftMotor*MAX_SPEED);
//
//  analogWrite(RIGHT_MOTOR1_PIN, rightMotor > 0 ? 0                    : rightMotor*MAX_SPEED);
//  analogWrite(RIGHT_MOTOR2_PIN, rightMotor > 0 ? rightMotor*MAX_SPEED : 0);
}
