#include <stdio.h>
#include <wiringPi.h>

// 定义舵机连接的GPIO引脚
#define SERVO_PIN 4

// 定义舵机运动角度范围
#define MIN_ANGLE 0
#define MAX_ANGLE 180

// 将角度转换为舵机控制信号脉冲宽度
int angleToPulseWidth(int angle) {
    return (int)(((double)angle / 180) * 2000) + 500;
}


int main() {
    // 初始化WiringPi库
    if (wiringPiSetupGpio() == -1) {
        printf("无法初始化WiringPi库\n");
        return 1;
    }

    // 设置舵机引脚为输出模式
    pinMode(SERVO_PIN, OUTPUT);

    while (1) {
        int angle;

        // 从用户输入获取舵机角度
        printf("请输入舵机角度（0-180）：");
        scanf("%d", &angle);

        // 检查角度是否在合法范围内
        if (angle < MIN_ANGLE || angle > MAX_ANGLE) {
            printf("舵机角度超出范围\n");
            continue;
        }

        // 将角度转换为脉冲宽度
        int pulseWidth = angleToPulseWidth(angle);

        // 输出脉冲信号控制舵机
        digitalWrite(SERVO_PIN, HIGH);
        delayMicroseconds(pulseWidth);
        digitalWrite(SERVO_PIN, LOW);

        // 等待一段时间，以便舵机稳定
        delay(1000);
    }

    return 0;
}
