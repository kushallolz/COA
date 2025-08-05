#include <stdio.h>
int main() {
    int num;
    // Get input from user
    printf("Enter a number: ");
    scanf("%d", &num);
    // Calculate 2's complement
    // 2's complement = 1's complement + 1
    int twos_complement = (~num) + 1;
    // Display results
    printf("Original number: %d\n", num);
    // Display in binary for better understanding
    printf("Original number in binary: ");
    for(int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if(i % 4 == 0) printf(" "); // Add space for readability
    }
    printf("\n2's complement in binary: ");
    for(int i = 31; i >= 0; i--) {
        printf("%d", (twos_complement >> i) & 1);
        if(i % 4 == 0) printf(" "); // Add space for readability
    }
    printf("\n");
    return 0;
}
