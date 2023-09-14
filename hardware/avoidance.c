#include "../include/avoidance.h"
const int minDistance = 20;

void avoidance_cleanup() {
    //car_cleanup();
    duoji_cleanup();
    distance_cleanup();
}

void avoidance_init() {
    //car_init();
    duoji_init();
    distance_init();
}


void *avoidance_run(void *param) {
    while (TRUE) {
        check_forward();
        delay(100);
        while (get_distance() > minDistance) {
            go_up();
            delay(100);
        }
        go_stop();
        delay(100);
        check_left();
        delay(500);
        if (get_distance() > minDistance) {
            go_left();
        } else {
            check_right();
            delay(500);
            if (get_distance() > minDistance) {
                go_right();
            }
        }
    }
}

// void *avoidance_run(void *param) {
//     while (TRUE) {
//         check_forward();
//         delay(100);
//         while (get_distance() > minDistance) {
//             go_up();
//             delay(100);
//         }
//         go_stop();
//         delay(100);
//         while (TRUE) {
//             //check_forward();
//             check_left();
//             delay(500);
//             if (get_distance() > minDistance) {
//                 go_left();
//                 break;
//             } else {
//                 check_right();
//                 delay(500);
//                 if (get_distance() > minDistance) {
//                     go_right();
//                     break;
//                 } else continue;
//             }
//         }
//     }
// }

// void cleanup() {
//     avoidance_cleanup();
//     exit(0);
// }
// int main() {
//     if (wiringPiSetupGpio() < 0) {
//         perror("error!");
//         exit(1);
//     }
//     signal(SIGINT, cleanup);
//     avoidance_init();
//     avoidance_run();
    
//     return 0;
// }







