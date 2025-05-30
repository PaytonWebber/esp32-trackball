#include "pmw3360_sensor.hpp"

PMW3360_Sensor sensor;

void setup() {
  Serial.begin(115200);
  delay(1000);
  sensor.begin();
}

void loop() {
  if (sensor.has_update()) {
    MouseUpdate update = sensor.get_update();
    Serial.print("dx: ");
    Serial.print(update.dx);
    Serial.print(" dy: ");
    Serial.println(update.dy);
  }
  delay(10);
}
