#include "../include/led.h"

void led_init() {
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
}

void led_cleanup() {
    pinMode(R, INPUT);
    pinMode(G, INPUT);
    pinMode(B, INPUT);
}

void open_led() {
    digitalWrite(R, HIGH);
    sleep(1);
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    sleep(1);
    digitalWrite(G, LOW);
    digitalWrite(B, HIGH);
    sleep(1);
    digitalWrite(B, LOW);
    sleep(1);
}
//
// int main() {
//     wiringPiSetupGpio();
//     pinMode(13, OUTPUT);
//     softPwmCreate(13, 0, 100);
//     for (int i = 0; i < 100; i++) {
//         softPwmWrite(13, i);
//         usleep(100000);
//     }
//     sleep(1);
//     pinMode(13, INPUT);
//     return 0;
// }
    //T = pwmRange * 0.1ms
    //T1 = 
//


// int main() {
//     wiringPiSetupGpio();
//     led_init();
//     open_led();
//     led_cleanup();   
    
//     return 0;
// }