/* Arduino Nofrendo
 * Please check hw_config.h and display.cpp for configuration details
 */
#include <stdio.h>
#include <esp_wifi.h>
#include <esp_task_wdt.h>
#include <FFat.h>
#include <SPIFFS.h>
#include <SD.h>
#include <SD_MMC.h>

#include <Arduino_GFX_Library.h>

#include "hw_config.h"

extern "C" {
#include "src/util/nofrendo/nofrendo.h"
}

int16_t bg_color;
extern Arduino_TFT *gfx;
extern void display_begin();

void setup() {
  Serial.begin(115200);

  // turn off WiFi
  esp_wifi_deinit();

  // disable Core 0 WDT
  // TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU(0);
  // esp_task_wdt_delete(idle_0);

  // start display
  display_begin();

  // filesystem defined in hw_config.h
  FILESYSTEM_BEGIN
  
  Serial.println("NoFrendo start!\n");
  nofrendo_main();
  Serial.println("NoFrendo end!\n");
}

void loop() {
}
