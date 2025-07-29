#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to convert decimal to binary
void decimalToBinary(int num) {
    int binary[32];
    int i = 0;

    if (num == 0) {
        printf("Binary: 0\n");
        return;
    }

    while (num > 0) {
        binary[i] = num % 2;
        num = num / 2;
        i++;
    }

    printf("Binary: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", binary[j]);
    printf("\n");
}

// Function to convert binary to decimal
int binaryToDecimal(char binaryStr[]) {
    int len = strlen(binaryStr);
    int decimal = 0;

    for (int i = 0; i < len; i++) {
        if (binaryStr[i] != '0' && binaryStr[i] != '1') {
            printf("Invalid binary number.\n");
            return -1;
        }
        decimal = decimal * 2 + (binaryStr[i] - '0');
    }

    return decimal;
}

int main() {
    int choice;
    printf("Choose conversion type:\n");
    printf("1. Decimal to Binary\n");
    printf("2. Binary to Decimal\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int decimal;
        printf("Enter a decimal number: ");
        scanf("%d", &decimal);
        decimalToBinary(decimal);
    } else if (choice == 2) {
        char binaryStr[65];
        printf("Enter a binary number: ");
        scanf("%s", binaryStr);
        int result = binaryToDecimal(binaryStr);
        if (result != -1)
            printf("Decimal: %d\n", result);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
