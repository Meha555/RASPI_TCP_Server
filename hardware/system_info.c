#include "../include/system_info.h"

void getCPUtemperature(char *res) {
    FILE *fp;
    //char *res = (char*)malloc(sizeof(char) * 10);
    char buffer[128];

    fp = popen("vcgencmd measure_temp", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    fgets(buffer, sizeof(buffer), fp);
    pclose(fp);

    sscanf(buffer, "temp=%s'C\n", res);
    //return res;
}

// Index 0: total RAM
// Index 1: used RAM
// Index 2: free RAM
void getRAMinfo(unsigned long* ramInfo) {
    FILE *fp;
    //unsigned long *ramInfo = (unsigned long*)malloc(sizeof(unsigned long) * 3);
    char buffer[128];

    fp = popen("free", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    for (int i = 0; i < 2; i++)
        fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);

    sscanf(buffer, "%*s %lu %lu %lu", &ramInfo[0], &ramInfo[1], &ramInfo[2]);

    pclose(fp);
    //return ramInfo;
}

void getCPUuse(char *cpuUsage) {
    FILE *fp;
    //char *cpuUsage = (char*)malloc(sizeof(char) * 10);
    char buffer[128];

    fp = popen("top -n1 | awk '/Cpu\\(s\\):/ {print $2}'", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    fgets(buffer, sizeof(buffer), fp);
    pclose(fp);

    sscanf(buffer, "%s", cpuUsage);
    //return cpuUsage;
}

// Index 0: Filesystem
// Index 1: total disk space
// Index 2: used disk space
// Index 3: remaining disk space
// Index 4: percentage of disk used
void getDiskSpace(char (*diskInfo)[20]) {
    FILE *fp;
    //char **diskInfo = (char**)malloc(sizeof(char*) * 5);
    // for (int i = 0; i < 5; i++)
    //     diskInfo[i] = (char*)malloc(sizeof(char) * 20);
    char buffer[128];

    fp = popen("df -h /", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    //前两行是不必要的信息
    for (int i = 0; i < 2; i++)
        fgets(buffer, sizeof(buffer), fp);
    //第三行是磁盘信息
    fgets(buffer, sizeof(buffer), fp);

    sscanf(buffer, "%s %s %s %s %s", diskInfo[0], diskInfo[1],
           diskInfo[2], diskInfo[3], diskInfo[4]);

    pclose(fp);
    //return diskInfo;
}

void getSystemInfo(char *info) {
    char cpuTem[10];
    unsigned long ramInfo[3];
    char cpuUsage[10];
    char diskInfo[5][20];

    double RAM_total, RAM_used, RAM_free;

    char *DISK_total, *DISK_used, *DISK_perc;

    getCPUtemperature(cpuTem);
    getCPUuse(cpuUsage);
    getRAMinfo(ramInfo);
    RAM_total = (double)ramInfo[0] / 1000;
    RAM_used = (double)ramInfo[1] / 1000;
    RAM_free = (double)ramInfo[2] / 1000;
    getDiskSpace(diskInfo);
    DISK_total = diskInfo[1];
    DISK_used = diskInfo[2];
    DISK_perc = diskInfo[4];

    sprintf(info, "CPU Temperature = %s\n\
CPU Use = %s\n\
RAM Total = %.1f MB\n\
RAM Used = %.1f MB\n\
RAM Free = %.1f MB\n\
DISK Total Space = %sB\n\
DISK Used Space = %sB\n\
DISK Used Percentage = %s\n", cpuTem, cpuUsage, RAM_total, RAM_used, RAM_free, DISK_total, DISK_used, DISK_perc);
}

// int main() {
//     char *CPU_temp;
//     char *CPU_usage;
//     unsigned long *RAM_stats;
//     double RAM_total, RAM_used, RAM_free;
//     char **DISK_stats;
//     char *DISK_total, *DISK_used, *DISK_perc;

//     CPU_temp = getCPUtemperature();
//     CPU_usage = getCPUuse();
//     RAM_stats = getRAMinfo();
//     RAM_total = (double)RAM_stats[0] / 1000;
//     RAM_used = (double)RAM_stats[1] / 1000;
//     RAM_free = (double)RAM_stats[2] / 1000;
//     DISK_stats = getDiskSpace();
//     DISK_total = DISK_stats[1];
//     DISK_used = DISK_stats[2];
//     DISK_perc = DISK_stats[4];

//     printf("\n");
//     printf("CPU Temperature = %s\n", CPU_temp);
//     printf("CPU Use = %s\n", CPU_usage);
//     printf("\n");
//     printf("RAM Total = %.1f MB\n", RAM_total);
//     printf("RAM Used = %.1f MB\n", RAM_used);
//     printf("RAM Free = %.1f MB\n", RAM_free);
//     printf("\n");
//     printf("DISK Total Space = %sB\n", DISK_total);
//     printf("DISK Used Space = %sB\n", DISK_used);
//     printf("DISK Used Percentage = %s\n", DISK_perc);

//     // Free allocated memory
//     free(CPU_temp);
//     free(CPU_usage);
//     free(RAM_stats);
//     for (int i = 0; i < 5; i++)
//         free(DISK_stats[i]);
//     free(DISK_stats);

//     return 0;
// }