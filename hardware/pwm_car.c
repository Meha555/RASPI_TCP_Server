#include "../include/pwm_car.h"
const int pwm_maxSpeed = 50;
const int pwm_minSpeed = 15;
bool pwm_move_forward = TRUE;
void pwm_car_cleanup() {
    softPwmWrite(t1, 0);
    softPwmWrite(t2, 0);
    softPwmWrite(t3, 0);
    softPwmWrite(t4, 0);

    pinMode(t1, INPUT);
    pinMode(t2, INPUT);
    pinMode(t3, INPUT);
    pinMode(t4, INPUT);
}

// void cleanup() {
//     car_cleanup();
//     exit(0);
// }

void speedUp() {
    int i = pwm_minSpeed;
    if (pwm_move_forward) {
        while (++i < pwm_maxSpeed) {
            softPwmWrite(t1, i);
            softPwmWrite(t4, i);
            delay(100);
        }
    } else {
        while (++i < pwm_maxSpeed) {
            softPwmWrite(t2, i);
            softPwmWrite(t3, i);
            delay(100);
        }
    }
    
}

void speedDown() {
    int i = pwm_maxSpeed;
    if (pwm_move_forward) {
        while (--i > pwm_minSpeed) {
            softPwmWrite(t1, i);
            softPwmWrite(t4, i);
            delay(100);
        }
    } else {
        while (--i > pwm_minSpeed) {
            softPwmWrite(t2, i);
            softPwmWrite(t3, i);
            delay(100);
        }
    }
    
}

void pwm_car_init() {
    pinMode(t1, OUTPUT);
    pinMode(t2, OUTPUT);
    pinMode(t3, OUTPUT);
    pinMode(t4, OUTPUT);
    softPwmCreate(t1, 0, 100);
    softPwmCreate(t2, 0, 100);
    softPwmCreate(t3, 0, 100);
    softPwmCreate(t4, 0, 100);
}

// int main() {
//     wiringPiSetupGpio();
//     signal(SIGINT, cleanup);
//     car_init();

//     speedUp();
//     sleep(10);
//     speedDown();
//     move_forward = FALSE;
//     speedUp();
//     speedDown();

// //前进
//     // for (int i = 0; i < 100; i++) {
//     //     softPwmWrite(t1, i);
//     //     softPwmWrite(t4, i);
//     //     usleep(100000);
//     // }
//     // sleep(1);

//     // for (int i = 100; i > 0; i--) {
//     //     softPwmWrite(t1, i);
//     //     softPwmWrite(t4, i);
//     //     usleep(100000);
//     // }
//     // sleep(1);

// //后退
//     // for(int i = 0;i < 100;i++){
//     //     softPwmWrite(t2,i);
//     //     softPwmWrite(t3,i);
//     //     usleep(100000);
//     // }
//     // sleep(1);

//     // for(int i = 100;i > 0;i--){
//     //     softPwmWrite(t2,i);
//     //     softPwmWrite(t3,i);
//     //     usleep(100000);
//     // }
//     // sleep(1);

// //旋转
//     // for(int i = 0;i < 100;i++){
//     //     softPwmWrite(t1,i);
//     //     softPwmWrite(t3,i);
//     //     usleep(100000);
//     // }
//     // sleep(1);

//     // for(int i = 100;i > 0;i--){
//     //     softPwmWrite(t1,i);
//     //     softPwmWrite(t3,i);
//     //     usleep(100000);
//     // }
//     // sleep(1);

//     pinMode(t1, INPUT);
//     pinMode(t2, INPUT);
//     pinMode(t3, INPUT);
//     pinMode(t4, INPUT);
//     return 0;
// }