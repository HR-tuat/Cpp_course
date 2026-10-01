// 第11回：親のポインタから子の実装を呼ぶ

#include <Arduino.h>

#include "GPS.hpp"
#include "IMU.hpp"
#include "Sensor.hpp"

IMU imu;
GPS gps;

// 上位のコードは「Sensorであること」しか知らない
Sensor* sensors[] = {&imu, &gps};
const int SENSOR_COUNT = sizeof(sensors) / sizeof(sensors[0]);

void setup() {
    Serial.begin(115200);
}

void loop() {
    for (int i = 0; i < SENSOR_COUNT; i++) {
        sensors[i]->update();
        sensors[i]->print();
    }

    delay(1000);
}
