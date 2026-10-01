// 第2回：条件分岐・繰り返し
// if / else if / switch / for / while を1本のプログラムで動かす。
// 温度は固定値を少しずつ変えて、分岐の順番の意味を確かめる。

#include <Arduino.h>

const int BLINK_MS = 150;

/**
 * @brief 温度から警報の段階を決める
 * @details 上から順に評価されるため、条件の順番に意味がある。
 * @param temperature 温度(℃)
 * @return 0=normal, 1=warning, 2=danger
 */
int alarmLevel(float temperature) {
    if (temperature >= 40.0f) {
        return 2;
    } else if (temperature >= 30.0f) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief 警報の段階を文字列で表示する
 * @param level 警報の段階(0〜2)
 */
void printLevel(int level) {
    switch (level) {
    case 0:
        Serial.println("normal");
        break;

    case 1:
        Serial.println("warning");
        break;

    case 2:
        Serial.println("danger");
        break;

    default:
        Serial.println("unknown");
        break;
    }
}

/**
 * @brief 内蔵LEDを指定回数点滅させる
 * @param times 点滅回数
 */
void blink(int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(BLINK_MS);

        digitalWrite(LED_BUILTIN, LOW);
        delay(BLINK_MS);
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    delay(1000);

    Serial.println("--- for ---");
    for (int i = 0; i < 10; i++) {
        Serial.print(i);
        Serial.print(' ');
    }
    Serial.println();

    Serial.println("--- while ---");
    int countdown = 3;
    while (countdown > 0) {
        Serial.println(countdown);
        countdown--;
    }

    Serial.println("--- if / else if / switch ---");
}

void loop() {
    // 温度を 25.0 から 5.0 ずつ上げていき、分岐が切り替わる点を見る
    static float temperature = 25.0f;

    int level = alarmLevel(temperature);

    Serial.print(temperature);
    Serial.print(" -> ");
    printLevel(level);

    // 段階と同じ回数だけ点滅させる（normal のときは光らない）
    blink(level);

    temperature += 5.0f;
    if (temperature > 45.0f) {
        temperature = 25.0f;
    }

    delay(1000);
}
