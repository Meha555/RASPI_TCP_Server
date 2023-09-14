#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/reboot.h>

#define KEY     7

int main() {
    if (wiringPiSetup() < 0) {
        perror("error!");
        exit(1);
    }
    pinMode(KEY, INPUT);
    while (1) {
        if (digitalRead(KEY)) {
            sleep(0.02);
            if (digitalRead(KEY)) {
                while (digitalRead(KEY));
                sync();
                return reboot(RB_AUTOBOOT);
            }
            
        }
    }
}