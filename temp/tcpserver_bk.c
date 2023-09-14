#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tem.c"
#include "distance.c"
#include <signal.h>

void convertToString(unsigned char* array, int length, char* result) {
    for (int i = 0; i < length; i++) {
        unsigned int decimal = (unsigned int)array[i]; // 将十六进制数转化为十进制数
        sprintf(result + (i * 2), "%02u", decimal); // 使用%02u将十进制数格式化为两位宽度的字符串
    }
}

void cleanup() {
    distance_cleanup();
    exit(0);
}

void init_tcpserver() {
    
}
int main() {
    
    if (wiringPiSetupGpio() < 0) {
        perror("树莓派启动失败\n");
        return 1;
    }
    distance_init();
    signal(SIGINT, cleanup);
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if (listenfd < 0) {
        printf("socket error\n");
        return 0;
    }

    struct sockaddr_in svraddr;
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(8848);
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);


    if (bind(listenfd, (struct sockaddr*)&svraddr, sizeof(struct sockaddr)) < 0) {
        printf("bind error!\n");
        return 0;
    }


    if (listen(listenfd, 20) < 0) {
        printf("listen error\n");
        return 0;
    }

    struct sockaddr_in cliaddr = {};
    socklen_t cli_len = sizeof(cliaddr);

    int sockfd = accept(listenfd, (struct sockaddr*) &cliaddr, &cli_len);
    
    if (sockfd < 0) {
        printf("accept error!\n");
        return 0;
    } else {
        printf("accept\n");
    }

    while (1) {
        char buff[128] = { };
        char *p = buff;
        int n = recv(sockfd, buff, 127, 0);

        if (n <= 0) {
            printf("client will unlink\n");
            break;
        }
        printf("accept: %s \n", buff);
        memset(buff, 0, sizeof buff);

        unsigned char data[5]={};
        char dataStr[11] = {0};
        
        switch(dht11_read_data(data)){
            case 0:
                strcpy(p, "校验和出错"); p += 15;
                break;
            case 1:
                //char dataStr[5];
                //sprintf(dataStr,"%s",data);
                
                convertToString(data, 5, dataStr);
                printf("data:%d,%d,%d,%d,dataStr:%s", data[0], data[1], data[2], data[3], dataStr);
                strncpy(p, "温度=", 7); p += 7;
                strncpy(p, dataStr, 2); p += 2;
                strncpy(p, "，湿度=", 10); p += 10;
                strncpy(p, dataStr + 4, 2); p += 2;

                //strcpy(buff + 14, dataStr[5]);
                printf("温度=%d,湿度=%d\n",data[0],data[2]);
                break;
            case 2:
                strcpy(p, "dht11无响应"); p += 14; 
                break;
        }
        sleep(1);
        double distance = get_distance();
        char diststr[5];
        sprintf(diststr, "%.0lf", distance);
        strncpy(p, diststr, sizeof diststr); p += sizeof diststr;
        strcpy(p, "\0");
        printf("buff:%s\n", buff);
        send(sockfd, buff, 127, 0);

    }
    close(sockfd);
    close(listenfd);
    cleanup();
    return 0;
}