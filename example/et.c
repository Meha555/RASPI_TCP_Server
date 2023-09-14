#include <stdio.h>

void convertToString(unsigned char* array, int length, char* result) {
    int i;
    for (i = 0; i < length; i++) {
        unsigned int decimal = (unsigned int)array[i]; // 将十六进制数转化为十进制数
        sprintf(result + (i * 2), "%02u", decimal); // 使用%02u将十进制数格式化为两位宽度的字符串
    }
}

int main() {
    unsigned char array[] = {0x02, 0x10, 0x09};
    int length = sizeof(array) / sizeof(array[0]);

    char result[length * 2 + 1]; // Add space for null terminator

    convertToString(array, length, result);

    printf("Converted string: %s\n", result);

    return 0;
}