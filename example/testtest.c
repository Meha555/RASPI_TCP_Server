#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>
#include <softPwm.h>
#include <fcntl.h>
#include <linux/input.h>

#define t1 18
#define t2 23
#define t3 24
#define t4 25

int fd;

enum {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd',
    EXIT = 'q'
};

char keycode_to_key(int keycode) {
    // 这里是键码与字符的映射表
    // 你可以根据需要进行扩展
    switch (keycode) {
        case KEY_W:
            return 'w';
        case KEY_S:
            return 's';
        case KEY_A:
            return 'a';
        case KEY_D:
            return 'd';
        case KEY_Q:
            return 'q';
        default:
            return '\0';  // 如果键码没有对应的字符，则返回空字符
    }
}

void up() {
//前进

    softPwmWrite(t1, 100);
    softPwmWrite(t4, 100);
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
    softPwmWrite(t2, 100);
    softPwmWrite(t3, 100);
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
    softPwmWrite(t1,100);
    softPwmWrite(t3,100);
    usleep(80000);
    softPwmWrite(t1, 0);
    softPwmWrite(t3, 0);
}

void right() {
    //旋转
    softPwmWrite(t2, 100);
    softPwmWrite(t4, 100);
    usleep(80000);
    softPwmWrite(t2, 0);
    softPwmWrite(t4, 0);
}

void Exit() {
    //system("stty cooked");
    pinMode(t1, INPUT);
    pinMode(t2, INPUT);
    pinMode(t3, INPUT);
    pinMode(t4, INPUT);
    // 关闭输入设备文件
    close(fd);
    exit(0);
}

int main() {


    struct input_event ev;

    // 打开输入设备文件
    if ((fd = open("/dev/input/event1", O_RDONLY)) == -1) {
        perror("无法打开输入设备");
        exit(1);
    }

    

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
    //system("stty raw");


// 获取键盘事件
    while (1) {
        //printf("--------------");
        if (read(fd, &ev, sizeof(struct input_event)) == -1) {
            perror("读取输入事件失败");
            exit(1);
        }

        // 检查事件类型和键码
        //if (ev.type == EV_KEY && ev.value == 1) {
            command = keycode_to_key(ev.code);
            switch(command) {
            case UP: up();break;
            case DOWN: down();break;
            case LEFT: left();break;
            case RIGHT: right();break;
            case EXIT: Exit();break;
            default: break;
            }
        //}
    }
    
    return 0;
}