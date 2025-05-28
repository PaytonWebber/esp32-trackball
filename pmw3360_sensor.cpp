#include "pmw3360_sensor.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>

PMW3360_Sensor::PMW3360_Sensor() {
  pinMode(NCS_PIN, OUTPUT);
  digitalWrite(NCS_PIN, HIGH);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
}

void PMW3360_Sensor::begin() { power_up(); }

uint8_t PMW3360_Sensor::spi_read(uint8_t reg) {
  digitalWrite(NCS_PIN, LOW);
  SPI.transfer(reg & 0x7F);
  delayMicroseconds(160);
  uint8_t data = SPI.transfer(0);
  digitalWrite(NCS_PIN, HIGH);
  delayMicroseconds(20);

  return data;
}

void PMW3360_Sensor::spi_write(uint8_t reg, uint8_t data) {
  digitalWrite(NCS_PIN, LOW);
  SPI.transfer(reg | 0x80); // 1 as MSB to indicate direction
  SPI.transfer(data);
  delayMicroseconds(35);
  digitalWrite(NCS_PIN, HIGH);
  delayMicroseconds(120);
}

void PMW3360_Sensor::power_up() {
  reset_spi();
  spi_write(POWER_UP_RESET, 0x5A);
  delay(50);
  spi_read(0x02);
  spi_read(0x03);
  spi_read(0x04);
  spi_read(0x05);
  spi_read(0x06);
  srom_download();
}

void PMW3360_Sensor::reset_spi() {
  digitalWrite(NCS_PIN, HIGH);
  digitalWrite(NCS_PIN, LOW);
}

void PMW3360_Sensor::srom_download() {
  uint8_t config2_data = spi_read(CONFIG2);
  spi_write(CONFIG2,
            config2_data & 0xDF); // write 0 to REST_ENABLE bit of CONFIG2
  spi_write(SROM_ENABLE, 0x1D);
  delay(10);
  spi_write(SROM_ENABLE, 0x18);
  digitalWrite(NCS_PIN, LOW);
  SPI.transfer(SROM_LOAD_BURST | 0x80);
  delayMicroseconds(35);
  uint8_t d;
  for (std::size_t i = 0; i < firmware_length; i++) {
    d = firmware_data[i];
    SPI.transfer(d);
    delayMicroseconds(35);
  }
  digitalWrite(NCS_PIN, HIGH);
  delayMicroseconds(120);
  uint8_t srom_id = spi_read(SROM_ID);
  if (srom_id == 0x00) {
    Serial.println("SROM Download - FAILED.");
    while (true)
      ; // hang safely
  }
  Serial.println("SROM Download - SUCCESS.");
  spi_write(CONFIG2, 0x00);
}
void PMW3360_Sensor::shutdown() { spi_write(SHUTDOWN, 0xB6); }
bool PMW3360_Sensor::has_update() {
  spi_write(MOTION, 0x00);
  uint8_t motion = spi_read(MOTION);
  return (motion & 0x80);
}

MouseUpdate PMW3360_Sensor::get_update() {
  uint8_t dx_l = spi_read(DELTA_X_L);
  uint8_t dx_h = spi_read(DELTA_X_H);
  uint8_t dy_l = spi_read(DELTA_Y_L);
  uint8_t dy_h = spi_read(DELTA_Y_H);

  int16_t dx = (int16_t)((dx_h << 8) | dx_l);
  int16_t dy = (int16_t)((dy_h << 8) | dy_l);

  return MouseUpdate{dx, dy};
}
