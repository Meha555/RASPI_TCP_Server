#include "../include/key.h"

void key_cleanup() {
    digitalWrite(BEEP, 0);
    digitalWrite(R, 0);
    pinMode(BEEP, INPUT);
    pinMode(R, INPUT);
}

void key_init() {
    pinMode(BEEP, OUTPUT);
    pinMode(R, OUTPUT);
    digitalWrite(BEEP, 0);
    pinMode(KEY, INPUT);
}

// void cleanup(int signo) {
//     key_cleanup();
//     signal(SIGINT, SIG_DFL);
// }

// int main() {
//     if (wiringPiSetupGpio() < 0) {
//         perror("error!");
//         exit(1);
//     }
//     signal(SIGINT, cleanup);
//     key_init();
//     while (1) {
//         if (digitalRead(KEY)) {
//             delay(200);
//             if (digitalRead(KEY)) {
//                 puts("key pressed!");
//                 while (digitalRead(KEY));
//                 if (digitalRead(BEEP) == 0) {
//                     digitalWrite(BEEP, 1);
//                     digitalWrite(R, 1);
//                 } else {
//                     digitalWrite(BEEP, 0);
//                     digitalWrite(R, 0);
//                 }
//             }
            
//         }
//         sleep(1);
//     }
// }