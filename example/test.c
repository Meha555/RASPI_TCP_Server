#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <softPwm.h>
#define R 25
#define G 24
#define B 23

void cleanup(int sig) {
    pinMode(R, INPUT);
    pinMode(G, INPUT);
    pinMode(B, INPUT);
    exit(0);
}

int main(void) {
    if (wiringPiSetup() < 0) exit(0);
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
    signal(SIGINT, cleanup);
    while (1) {
        digitalWrite(R, 1);
        delay(1000);
        digitalWrite(R, 0);
        digitalWrite(G, 1);
        delay(1000);
        digitalWrite(G, 0);
        digitalWrite(B, 1);
        delay(1000);
        digitalWrite(B, 0);
    }
    return 0;
}