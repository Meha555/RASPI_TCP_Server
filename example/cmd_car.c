#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>
#include <softPwm.h>

#define t1 18
#define t2 23
#define t3 24
#define t4 25

enum {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd',
    EXIT = 'q'
};

void up() {
//前进

    softPwmWrite(t1, 80);
    softPwmWrite(t4, 80);
    usleep(80000);
    softPwmWrite(t1, 0);
    softPwmWrite(t4, 0);
    // sleep(1);

    // for (int i = 100; i > 0; i--) {
    //     softPwmWrite(t1, i);
    //     softPwmWrite(t4, i);
    //     usleep(100000);
    // }
    // sleep(1);
}

void down() {
//后
    softPwmWrite(t2, 80);
    softPwmWrite(t3, 80);
    usleep(80000);
    softPwmWrite(t2, 0);
    softPwmWrite(t3, 0);
    // sleep(1);

    // for(int i = 100;i > 0;i--){
    //     softPwmWrite(t2,i);
    //     softPwmWrite(t3,i);
    //     usleep(100000);
    // }
    // sleep(1);
}

void left() {
//旋转
    softPwmWrite(t1,80);
    softPwmWrite(t3,80);
    usleep(80000);
    softPwmWrite(t1, 0);
    softPwmWrite(t3, 0);
}

void right() {
    //旋转
    softPwmWrite(t2, 80);
    softPwmWrite(t4, 80);
    usleep(80000);
    softPwmWrite(t2, 0);
    softPwmWrite(t4, 0);
}

void Exit() {
    system("stty cooked");
    pinMode(t1, INPUT);
    pinMode(t2, INPUT);
    pinMode(t3, INPUT);
    pinMode(t4, INPUT);
    exit(0);
}

int main() {
    wiringPiSetupGpio();
    pinMode(t1, OUTPUT);
    pinMode(t2, OUTPUT);
    pinMode(t3, OUTPUT);
    pinMode(t4, OUTPUT);
    softPwmCreate(t1, 0, 100);
    softPwmCreate(t2, 0, 100);
    softPwmCreate(t3, 0, 100);
    softPwmCreate(t4, 0, 100);
    int command = -1;
    system("stty raw");

    while (TRUE) {
        command = getchar();
        switch(command) {
            case UP: up();break;
            case DOWN: down();break;
            case LEFT: left();break;
            case RIGHT: right();break;
            case EXIT: Exit();break;
            default: break;
        }
    }
    return 0;
}