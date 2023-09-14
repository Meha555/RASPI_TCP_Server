#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#define CLK 22
#define DIO 27
#define wenshi 5
int segdata[11] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 113}; //0-9f


int dht11_scan();

//复位函数(启动)
void dht11_reset(){
    pinMode(wenshi,OUTPUT);
    delay(10);
    digitalWrite(wenshi,1);
    delayMicroseconds(10);
    digitalWrite(wenshi,0);
    delay(18);
    digitalWrite(wenshi,1);
    delayMicroseconds(30);
    pinMode(wenshi,INPUT);
    delayMicroseconds(50);
}
//读取一个位
char read_bit(){
    while(!dht11_scan());
    delayMicroseconds(40);
    int timeout = 1000;
    if(dht11_scan()){
        while (dht11_scan() && timeout-- > 0);
        if (timeout <= 0) printf("timeout!");
        return 1;
    }else{
        return 0;
    }
}

//读取一个字节
unsigned char read_byte(){
    unsigned char data = 0;
    for (int i = 0;i < 8;i++){
        data <<= 1;
        data |= read_bit();
    }
    return data;
}

//扫描高低电平
int dht11_scan(){
    return digitalRead(wenshi);
}

//读取40位数据
int dht11_read_data(int *buff){
    //char i = 0;
    dht11_reset();
    if(!dht11_scan()){
        while(!dht11_scan()) printf("scaning\n");
        while(dht11_scan());
        for(int i = 0;i < 5;i++){
            buff[i] = read_byte();
        }

        int checksum = buff[0] + buff[1] + buff[2] + buff[3];
        if(checksum != buff[4]){
            return 0;
        }else{
            return 1;
        }

    }
    return 2;
}

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
    clean();
    pinMode(wenshi, INPUT);
    digitalWrite(DIO, LOW);
    digitalWrite(CLK, LOW);
    pinMode(DIO, INPUT);
    pinMode(CLK, INPUT);
    
    exit(0);
}

int main() {
    signal(SIGINT, cleanup);
    int data[5] = {};
    wiringPiSetupGpio();
    pinMode(DIO, OUTPUT);
    pinMode(CLK, OUTPUT);
    bool dot = TRUE;
    while (TRUE) {
        int state = dht11_read_data(data);
        if (state == 1) set_num_display(data[0] / 10, data[0] % 10, data[2] / 10, data[2] % 10, dot);
        else set_num_display(10, 10, 10, 10, dot);
        sleep(1);
    }
    return 0;

}
