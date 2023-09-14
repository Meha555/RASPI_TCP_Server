
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <softPwm.h>
double get_distance() {
    printf("begin\n");
    usleep(100000);
    digitalWrite(TRIG, LOW);
    delayMicroseconds(140);
    //开始信号
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    delayMicroseconds(140);

    while (digitalRead(ECHO) == LOW);// printf("=");   //等到ECHO引脚返回高电平信号
    time_t time1 = micros();
    while (digitalRead(ECHO) == HIGH);// printf("+");  //等到ECHO的高电平结束
    time_t time2 = micros();

    double distance = (time2 - time1) * 340 * 100 / 2 / 1000000.0;
    printf("end\n");
    return distance;
}

void cleanup() {
    digitalWrite(TRIG, LOW);
    digitalWrite(ECHO, LOW);
    digitalWrite(t1, LOW);
    digitalWrite(t2, LOW);
    digitalWrite(t3, LOW);
    digitalWrite(t4, LOW);
    pinMode(t1, INPUT);
    pinMode(t2, INPUT);
    pinMode(t3, INPUT);
    pinMode(t4, INPUT);
    pinMode(TRIG, INPUT);
    pinMode(ECHO, INPUT);
    exit(0);
}

int main() {
    wiringPiSetupGpio();
    signal(SIGINT, cleanup);
    pinMode(t1, OUTPUT);
    pinMode(t2, OUTPUT);
    pinMode(t3, OUTPUT);
    pinMode(t4, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    softPwmCreate(t1, 0, 100);
    softPwmCreate(t2, 0, 100);
    softPwmCreate(t3, 0, 100);
    softPwmCreate(t4, 0, 100);

//前进
    while (TRUE) { 
        while (get_distance() < 20) {
            softPwmWrite(t1, 0);
            softPwmWrite(t4, 0);
            //sleep(1);
            printf("--------\n");
        }
        printf("tiao\n");
        softPwmWrite(t1, 80);
        softPwmWrite(t4, 80);
        //sleep(1);
    }
    return 0;
}