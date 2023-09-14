#include <wiringPi.h>

#define PWM_PIN 4 // 使用 GPIO1（物理引脚12）作为 PWM 输出

int main(void) {
    if (wiringPiSetupGpio() == -1)
        return 1;

    int range = 200; // 设置 PWM 范围
    int step = 10; // 每次增加或减少的步长
    int angle = 90; // 设置初始角度

    pinMode(PWM_PIN, OUTPUT);

    while (1) {
        // 将舵机转到指定角度
        digitalWrite(PWM_PIN, HIGH);
        delayMicroseconds(angle * 10); // 设置高电平持续时间
        digitalWrite(PWM_PIN, LOW);
        delayMicroseconds((range - angle) * 10); // 设置低电平持续时间

        delay(1000); // 延迟一段时间，以便观察舵机运动

        angle += step;
        if (angle >= range || angle <= 0) {
            step = -step; // 角度超过范围则反向增减
        }
    }

    return 0;
}
