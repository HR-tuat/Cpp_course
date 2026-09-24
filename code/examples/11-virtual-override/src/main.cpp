// 第13回：種類の違うセンサを同じ手続きで扱う

#include <Arduino.h>

#include "GPS.h"
#include "IMU.h"
#include "Sensor.h"

IMU imu;
GPS gps;

// 上位のコードは「Sensorであること」しか知らない
Sensor* sensors[] = {&imu, &gps};
const int SENSOR_COUNT = sizeof(sensors) / sizeof(sensors[0]);

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        sensors[i]->update();
        sensors[i]->print();
    }

    delay(1000);
}
