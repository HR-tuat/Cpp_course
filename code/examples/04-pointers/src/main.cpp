// 第4回：配列・メモリ・ポインタ・参照
// 「アドレス」と「値」を並べて表示し、ポインタと参照の違いを確かめる。

#include <Arduino.h>

const int SENSOR_COUNT = 5;

/**
 * @brief 配列の最大値を求める
 * @param values 値の配列
 * @param count 要素数
 * @return 最大値
 */
int findMax(const int values[], int count) {
    int max = values[0];

    for (int i = 1; i < count; i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }

    return max;
}

/**
 * @brief ポインタ経由で呼び出し元の変数を1増やす
 * @param[in,out] value 増やす変数へのポインタ
 */
void addOne(int* value) {
    *value = *value + 1;
}

/**
 * @brief 参照経由で呼び出し元の変数を1増やす
 * @param[in,out] value 増やす変数への参照
 */
void addOneRef(int& value) {
    value = value + 1;
}

/**
 * @brief 値をコピーして受け取り、1増やす（呼び出し元は変わらない）
 * @param value 増やす値
 */
void addOneCopy(int value) {
    value = value + 1;
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    int values[SENSOR_COUNT] = {120, 340, 95, 870, 410};

    Serial.println("--- 配列 ---");
    for (int i = 0; i < SENSOR_COUNT; i++) {
        Serial.print("values[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(values[i]);
    }

    Serial.print("max = ");
    Serial.println(findMax(values, SENSOR_COUNT));

    Serial.println("--- アドレスと値 ---");
    int value = 10;
    int* ptr = &value;

    Serial.print("value    = ");
    Serial.println(value);
    Serial.print("&value   = 0x");
    Serial.println((uintptr_t)&value, HEX);
    Serial.print("ptr      = 0x");
    Serial.println((uintptr_t)ptr, HEX);  // &value と同じ
    Serial.print("*ptr     = ");
    Serial.println(*ptr);                // value と同じ

    *ptr = 20;
    Serial.print("*ptr = 20 のあと value = ");
    Serial.println(value);  // 20

    Serial.println("--- 参照 ---");
    int& ref = value;
    ref = 30;
    Serial.print("ref = 30 のあと value = ");
    Serial.println(value);  // 30

    Serial.println("--- 関数に渡す ---");
    int n = 0;

    addOneCopy(n);
    Serial.print("addOneCopy の後 : ");
    Serial.println(n);  // 0（コピーを増やしただけ）

    addOne(&n);
    Serial.print("addOne     の後 : ");
    Serial.println(n);  // 1

    addOneRef(n);
    Serial.print("addOneRef  の後 : ");
    Serial.println(n);  // 2
}

void loop() {
}
