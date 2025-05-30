#include "pmw3360_sensor.hpp"
#include <USB.h>
#include <USBHIDMouse.h>

PMW3360_Sensor sensor;
USBHIDMouse Mouse;

void setup() {
  Serial.begin(115200);
  delay(1000);
  sensor.begin();
  USB.begin();
  Mouse.begin();
}

void loop() {
  // if (sensor.has_update()) {
  //   BurstMotionReport report = sensor.get_burst_update();

  //   Serial.print("dx: ");
  //   Serial.print(report.delta_x);
  //   Serial.print(" dy: ");
  //   Serial.print(report.delta_y);
  //   Serial.print(" SQUAL: ");
  //   Serial.print(report.squal);
  //   Serial.print(" RawSum: ");
  //   Serial.print(report.raw_sum);
  //   Serial.print(" Shutter: ");
  //   Serial.println(report.shutter);
  // }
  //
  if (sensor.has_update()) {
    BurstMotionReport report = sensor.get_burst_update();
    Mouse.move(report.delta_x, report.delta_y);
  }

  delay(1);
}
