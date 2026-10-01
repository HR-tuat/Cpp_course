// 第9回：状態を enum class で管理する

#include <Arduino.h>

enum class RobotState {
    STOP,
    MOVE,
    ERROR
};

// ボード上の内蔵LED。配線なしで光る
const int LED_PIN = LED_BUILTIN;

RobotState state = RobotState::STOP;

/**
 * @brief 状態を切り替える
 * @details 切り替えをこの関数1つに通しておくと、
 *          どこから状態が変わったのかを追いやすい。
 * @param next 次の状態
 */
void setState(RobotState next) {
    state = next;
}

/**
 * @brief 現在の状態に応じてLEDを制御する
 */
void updateLed() {
    switch (state) {
    case RobotState::STOP:
        digitalWrite(LED_PIN, LOW);
        break;

    case RobotState::MOVE:
        digitalWrite(LED_PIN, HIGH);
        break;

    case RobotState::ERROR:
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
        break;
    }
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    setState(RobotState::MOVE);
}

void loop() {
    updateLed();
    delay(50);
}
