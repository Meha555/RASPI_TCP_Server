#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//char *res = (char*)malloc(sizeof(char) * 10);
void getCPUtemperature(char *);

//unsigned long *ramInfo = (unsigned long*)malloc(sizeof(unsigned long) * 3);
void getRAMinfo(unsigned long*);

//char *cpuUsage = (char*)malloc(sizeof(char) * 10);
void getCPUuse(char*);

//char **diskInfo = (char**)malloc(sizeof(char*) * 5);
// for (int i = 0; i < 5; i++)
//     diskInfo[i] = (char*)malloc(sizeof(char) * 20);
void getDiskSpace(char (*diskInfo)[20]);

void getSystemInfo(char *);

#endif //SYSTEM_INFO_H