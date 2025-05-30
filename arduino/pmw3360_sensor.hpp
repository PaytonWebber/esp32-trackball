#ifndef PMW3360_SENSOR_H
#define PMW3360_SENSOR_H

#include "pmw3360_firmware.hpp"
#include <Arduino.h>
#include <SPI.h>
#include <cstdint>

extern const std::size_t firmware_length;
extern const uint8_t firmware_data[firmware_length];

// PMW3360-T2QU Registers
#define PRODUCT_ID 0x00
#define REVISION_ID 0x01
#define MOTION 0x02
#define DELTA_X_L 0x03
#define DELTA_X_H 0x04
#define DELTA_Y_L 0x05
#define DELTA_Y_H 0x06
#define SQUAL 0x07
#define PIXEL_SUM 0x08
#define MAXIMUM_PIXEL 0x09
#define MINIMUM_PIXEL 0x0A
#define SHUTTER_LOWER 0x0B
#define SHUTTER_UPPER 0x0A
#define CONTROL 0x0D
#define CONFIG1 0x0F
#define CONFIG2 0x10
#define ANGLE_TUNE 0x11
#define FRAME_CAPTURE 0x12
#define SROM_ENABLE 0x13
#define RUN_DOWNSHIFT 0x14
#define REST1_RATE_LOWER 0x15
#define REST1_RATE_UPPER 0x16
#define REST1_DOWNSHIFT 0x17
#define REST2_RATE_LOWER 0x18
#define REST2_RATE_UPPER 0x19
#define REST2_DOWNSHIFT 0x1A
#define REST3_RATE_LOWER 0x1B
#define REST3_RATE_UPPER 0x1C
#define OBSERVATION 0x24
#define DATA_OUT_LOWER 0x25
#define DATA_OUT_UPPER 0x26
#define PIXEL_DUMP 0x29
#define SROM_ID 0x2A
#define MIN_SQ_RUN 0x2B
#define PIXEL_THRESHOLD 0x2C
#define CONFIG5 0x2F
#define POWER_UP_RESET 0x3A
#define SHUTDOWN 0x3B
#define INVERSE_PRODUCT_ID 0x3F
#define LIFT_CUTOFF_TUNE3 0x41
#define ANGLE_SNAP 0x42
#define LIFT_CUTOFF_TUNE1 0x4A
#define MOTION_BURST 0x50
#define LIFT_CUTOFF_TUNE_TIMEOUT 0x58
#define LIFT_CUTOFF_TUNE_MIN_LENGTH 0x5A
#define SROM_LOAD_BURST 0x62
#define LIFT_CONFIG 0x63
#define PIXEL_BURST 0x64
#define LIFT_CUTOFF_TUNE2 0x65

constexpr uint8_t NCS_PIN = 10;

struct MouseUpdate {
  int16_t dx;
  int16_t dy;
};

class PMW3360_Sensor {
public:
  PMW3360_Sensor();
  void begin();
  void power_up();
  void shutdown();
  bool has_update();
  MouseUpdate get_update();

private:
  uint8_t spi_read(uint8_t reg);
  void spi_write(uint8_t reg, uint8_t data);
  void reset_spi();
  void srom_download();
};

#endif // PMW3360_SENSOR_H
