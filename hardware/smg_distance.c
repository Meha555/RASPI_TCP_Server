#include "../include/smg_distance.h"

// int segdata[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111}; //0-9

void *smg_show_distance(void *param) {
    bool dot = TRUE;
    while (TRUE) {
        double distance = get_distance();
        int big = (int)distance;
        double little = distance - big;
        set_num_display(distance / 10, (int)distance % 10, (int)(little * 10), (int)(little * 100) % 10, dot);
        sleep(1);
    }
}
// double get_distance() {
//     digitalWrite(TRIG, LOW);
//     delayMicroseconds(140);
//     //开始信号
//     digitalWrite(TRIG, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(TRIG, LOW);
//     delayMicroseconds(140);

//     while (digitalRead(ECHO) == LOW);   //等到ECHO引脚返回高电平信号
//     time_t time1 = micros();
//     while (digitalRead(ECHO) == HIGH);  //等到ECHO的高电平结束
//     time_t time2 = micros();

//     double distance = (time2 - time1) * 340 * 100 / 2 / 1000000.0;
//     return distance;
// }

// void start(){
//     digitalWrite(CLK, HIGH);
//     delayMicroseconds(140);
//     digitalWrite(DIO, HIGH);
//     delayMicroseconds(140);
//     digitalWrite(DIO, LOW);
//     delayMicroseconds(140);
//     digitalWrite(CLK, LOW);
//     delayMicroseconds(140);
// }
    

// void stop() {
//     digitalWrite(CLK, LOW);
//     delayMicroseconds(140);
//     digitalWrite(DIO, LOW);
//     delayMicroseconds(140);
//     digitalWrite(CLK, HIGH);
//     delayMicroseconds(140);
//     digitalWrite(DIO, HIGH);
//     delayMicroseconds(140);
// }
    

// void write_bit(int bit) {
//     digitalWrite(CLK, LOW);
//     delayMicroseconds(140);
//     digitalWrite(DIO, bit);
//     delayMicroseconds(140);
//     digitalWrite(CLK, HIGH);
//     delayMicroseconds(140);
// }
    

// void write_byte(int byte) {
//     for (int i = 0; i < 8; i++){
//         write_bit((byte >> i) & 1);
//     }
//     digitalWrite(CLK, LOW);
//     delayMicroseconds(140);
//     digitalWrite(DIO, HIGH);
//     delayMicroseconds(140);
//     digitalWrite(CLK, HIGH);
//     delayMicroseconds(140);
//     pinMode(DIO, INPUT);
//     while (digitalRead(DIO) == HIGH);
//     pinMode(DIO, OUTPUT);
// }
    

// void write_command(int cmd){
//     start();
//     write_byte(cmd);
//     stop();
// }
    

// void write_data(int addr, int data) {
//     start();
//     write_byte(addr);
//     write_byte(data);
//     stop();
// }
    

// void set_num_display(int n1, int n2, int n3, int n4, bool dp) {
//     write_command(64);
//     write_command(68);

//     write_data(192, segdata[n1]);
//     write_data(193, segdata[n2] + dp * 128);
//     write_data(194, segdata[n3]);
//     write_data(195, segdata[n4]);
//     write_command(136);
// }
    

// void clean() {
//     write_command(64);
//     write_command(68);

//     write_data(192, 0);
//     write_data(193, 0);
//     write_data(194, 0);
//     write_data(195, 0);
//     write_command(136);
// }

// void cleanup() {
//     clean();
//     digitalWrite(DIO, LOW);
//     digitalWrite(CLK, LOW);
//     pinMode(DIO, INPUT);
//     pinMode(CLK, INPUT);
//     digitalWrite(TRIG, LOW);
//     digitalWrite(ECHO, LOW);
//     pinMode(TRIG, INPUT);
//     pinMode(ECHO, INPUT);
//     exit(0);
// }

// int main() {
//     signal(SIGINT, cleanup);
//     wiringPiSetupGpio();
//     pinMode(DIO, OUTPUT);
//     pinMode(CLK, OUTPUT);
//     pinMode(TRIG, OUTPUT);
//     pinMode(ECHO, INPUT);
//     bool dot = TRUE;
//     while (TRUE) {
//         double distance = get_distance();
//         int big = (int)distance;
//         double little = distance - big;
//         set_num_display(distance / 10, (int)distance % 10, (int)(little * 10), (int)(little * 100) % 10, dot);
//         sleep(1);
//     }
//     return 0;

// }