#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#define CLK 22
#define DIO 27
int segdata[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111}; //0-9

void start(){
    digitalWrite(CLK, HIGH);
    sleep(0.000140);
    digitalWrite(DIO, HIGH);
    sleep(0.000140);
    digitalWrite(DIO, LOW);
    sleep(0.000140);
    digitalWrite(CLK, LOW);
    sleep(0.000140);
}
    

void stop() {
    digitalWrite(CLK, LOW);
    sleep(0.000140);
    digitalWrite(DIO, LOW);
    sleep(0.000140);
    digitalWrite(CLK, HIGH);
    sleep(0.000140);
    digitalWrite(DIO, HIGH);
    sleep(0.000140);
}
    

void write_bit(int bit) {
    digitalWrite(CLK, LOW);
    sleep(0.000140);
    digitalWrite(DIO, bit);
    sleep(0.000140);
    digitalWrite(CLK, HIGH);
    sleep(0.000140);
}
    

void write_byte(int byte) {
    for (int i = 0; i < 8; i++){
        write_bit((byte >> i) & 1);
    }
    digitalWrite(CLK, LOW);
    sleep(0.000140);
    digitalWrite(DIO, HIGH);
    sleep(0.000140);
    digitalWrite(CLK, HIGH);
    sleep(0.000140);
    pinMode(DIO, INPUT);
    while (digitalRead(DIO) == HIGH);
    pinMode(DIO, OUTPUT);
}
    

void write_command(int cmd){
    start();
    write_byte(cmd);
    stop();
}
    

void write_data(int addr, int data) {
    start();
    write_byte(addr);
    write_byte(data);
    stop();
}
    

void set_num_display(int n1, int n2, int n3, int n4, bool dp) {
    write_command(64);
    write_command(68);

    write_data(192, segdata[n1]);
    write_data(193, segdata[n2] + dp * 128);
    write_data(194, segdata[n3]);
    write_data(195, segdata[n4]);
    write_command(136);
}
    

void clean() {
    write_command(64);
    write_command(68);

    write_data(192, 0);
    write_data(193, 0);
    write_data(194, 0);
    write_data(195, 0);
    write_command(136);
}

void cleanup() {
    digitalWrite(DIO, LOW);
    digitalWrite(CLK, LOW);
    pinMode(DIO, INPUT);
    pinMode(CLK, INPUT);
    exit(0);
}

int main() {
    signal(SIGINT, cleanup);
    wiringPiSetupGpio();
    pinMode(DIO, OUTPUT);
    pinMode(CLK, OUTPUT);
    bool dot = TRUE;
    while (TRUE) {
        set_num_display(1, 2, 3, 5, dot);
        sleep(0.5);
    }
    return 0;

}