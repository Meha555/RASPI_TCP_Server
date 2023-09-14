#include "track_avoidance.h"

bool MOVABLE = TRUE;
pthread_t distance_trd;

// enum {
//     RIGHT = 1,
//     LEFT = 2,
//     FORWORD = 3,
//     STOP = 4
// };

// void track_init() {
//     pinMode(LineR, INPUT);
//     pinMode(LineL, INPUT);
//     pinMode(LineM1, INPUT);
//     pinMode(LineM2, INPUT);
// }

// void cleanup() {
//     car_cleanup();
//     distance_cleanup();
//     pthread_cancel(distance_trd);
//     if (pthread_join(distance_trd)) {
//         printf("track_avoidance: distance_trd join error\n");
//     }
//     exit(0);
// }

void cancel_track_avoidance() {
    pthread_cancel(distance_trd);
    if (pthread_join(distance_trd, NULL)) {
        printf("track_avoidance: distance_trd join error\n");
    }
}

// void turn_right() {
//     softPwmWrite(t1, 70);
//     softPwmWrite(t3, 70);
//     while (!(digitalRead(LineM1) == HIGH || digitalRead(LineM2) == HIGH)) delay(10);
//     softPwmWrite(t1, 0);
//     softPwmWrite(t3, 0);
// }

// void turn_left() {
//     softPwmWrite(t2, 70);
//     softPwmWrite(t4, 70);
//     while (!(digitalRead(LineM1) == HIGH || digitalRead(LineM2) == HIGH)) delay(10);
//     softPwmWrite(t2, 0);
//     softPwmWrite(t4, 0);
// }

// int get_direction() {
//     if (digitalRead(LineL) == HIGH && digitalRead(LineR) == LOW
//     && digitalRead(LineM1) == LOW && digitalRead(LineM2) == LOW) {
//         //printf("左转\n");
//         return LEFT;
//     } else if (digitalRead(LineR) == HIGH && digitalRead(LineL) == LOW
//     && digitalRead(LineM1) == LOW && digitalRead(LineM2) == LOW) {
//         //printf("右转\n");
//         return RIGHT;
//     } else if (digitalRead(LineM1) == HIGH || digitalRead(LineM2) == HIGH) {
//         //printf("前进\n");
//         return FORWORD;
//     } else {
//         //printf("未识别到路\n");
//         return STOP;
//     }
//     //delay(10);
// }

void *track_avoidance(void *param) {
    if (pthread_create(&distance_trd, NULL, check_distance, NULL)) {
        printf("线程创建失败！\n");
        car_cleanup();
        distance_cleanup();
        exit(1);
    }

    while (TRUE) {
        if (!MOVABLE) {
            printf("not movable!\n");
            go_stop();
            delay(100);
            continue;
        }
        int direction = get_direction();
        switch(direction) {
        case RIGHT:
            turn_right();
            break;
        case LEFT:
            turn_left();
            break;
        case FORWORD:
            go_up();
            break;
        default:
            go_stop();
            break;
        }
        delay(10);
    }
}

void *check_distance(void *param) {
    while (TRUE) {
        if (get_distance() < 20) 
            MOVABLE = FALSE;            
        else 
            MOVABLE = TRUE;
        delay(100);
    }
}

// int main() {
//     if (wiringPiSetupGpio() < 0) {
//         perror("error!");
//         return -1;
//     }
//     ray_init();
//     car_init();
//     distance_init();
//     signal(SIGINT, cleanup);
//     //int tolerance = 100;
    
//     track_avoidance();
//     return 0;
// }   