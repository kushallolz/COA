#include <stdio.h>
#include <conio.h>

#define SIZE 5

int A[SIZE] = {0}, Q[SIZE], M[SIZE], temp[SIZE];
int count = SIZE;

void decimalToBinary(int num, int bin[]) {
    int i;
    for (i = SIZE - 1; i >= 0; i--) {
        bin[i] = num % 2;
        num = num / 2;
    }
}

int binaryToDecimal(int bin[]) {
    int i, value = 0;
    for (i = 0; i < SIZE; i++) {
        value = value * 2 + bin[i];
    }
    return value;
}

void leftShift() {
    int i;
    for (i = 0; i < SIZE - 1; i++) {
        A[i] = A[i + 1];
    }
    A[SIZE - 1] = Q[0];
    for (i = 0; i < SIZE - 1; i++) {
        Q[i] = Q[i + 1];
    }
    Q[SIZE - 1] = 0;
}

void subtract(int A[], int M[]) {
    int i, B[SIZE], carry = 1;
    for (i = 0; i < SIZE; i++) {
        B[i] = M[i] == 0 ? 1 : 0;
    }
    for (i = SIZE - 1; i >= 0; i--) {
        if (B[i] == 1 && carry == 1) {
            B[i] = 0;
        } else if (carry == 1) {
            B[i] = 1;
            carry = 0;
        }
    }
    carry = 0;
    for (i = SIZE - 1; i >= 0; i--) {
        temp[i] = A[i] + B[i] + carry;
        if (temp[i] >= 2) {
            temp[i] = temp[i] % 2;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    for (i = 0; i < SIZE; i++) {
        A[i] = temp[i];
    }
}

void add(int A[], int M[]) {
    int i, carry = 0;
    for (i = SIZE - 1; i >= 0; i--) {
        temp[i] = A[i] + M[i] + carry;
        if (temp[i] >= 2) {
            temp[i] = temp[i] % 2;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    for (i = 0; i < SIZE; i++) {
        A[i] = temp[i];
    }
}

int isNegative(int A[]) {
    return A[0];
}

void displayRegisters() {
    int i;
    printf("A: ");
    for (i = 0; i < SIZE; i++) printf("%d", A[i]);
    printf("  Q: ");
    for (i = 0; i < SIZE; i++) printf("%d", Q[i]);
    printf("\n");
}

void restoringDivision() {
    int i;
    printf("\nInitial values:\n");
    displayRegisters();
    for (i = 0; i < SIZE; i++) {
        printf("\nStep %d:\n", i + 1);
        leftShift();
        printf("After shift:\n");
        displayRegisters();
        subtract(A, M);
        printf("After A = A - M:\n");
        displayRegisters();
        if (isNegative(A)) {
            add(A, M);
            Q[SIZE - 1] = 0;
            printf("A was negative, restoring A and setting Q0 = 0\n");
        } else {
            Q[SIZE - 1] = 1;
            printf("A was positive, setting Q0 = 1\n");
        }
        displayRegisters();
    }
}

int main() {
    int dividend, divisor, i;
    clrscr();
    printf("Enter dividend (0-31): ");
    scanf("%d", &dividend);
    printf("Enter divisor (1-31): ");
    scanf("%d", &divisor);
    if (divisor == 0) {
        printf("Error: Division by zero!\n");
        getch();
        return 0;
    }
    decimalToBinary(dividend, Q);
    decimalToBinary(divisor, M);
    for (i = 0; i < SIZE; i++) {
        A[i] = 0;
    }
    restoringDivision();
    printf("\nFinal Quotient (Q): ");
    for (i = 0; i < SIZE; i++) {
        printf("%d", Q[i]);
    }
    printf("\nFinal Remainder (A): ");
    for (i = 0; i < SIZE; i++) {
        printf("%d", A[i]);
    }
    printf("\n\nQuotient (Decimal): %d", binaryToDecimal(Q));
    printf("\nRemainder (Decimal): %d", binaryToDecimal(A));
    getch();
    return 0;
}
