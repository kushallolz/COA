#include <stdio.h>
#include <stdlib.h>

// Function to perform right shift on A, Q, and Q_1
void rightShift(int *A, int *Q, int *Q_1, int n) {
    *Q_1 = (*Q & 1); // Store LSB of Q
    *A = (*A >> 1) | ((*A & (1 << (n-1))) ? (1 << (n-1)) : 0); // Arithmetic right shift for A
    *Q = (*Q >> 1) | ((*A & 1) << (n-1)); // Shift Q, taking LSB of A
}

// Function to add two binary numbers (A + M)
void add(int *A, int M, int n) {
    int i, carry = 0;
    for (i = 0; i < n; i++) {
        int bitA = (*A >> i) & 1;
        int bitM = (M >> i) & 1;
        int sum = bitA ^ bitM ^ carry;
        carry = (bitA & bitM) | (bitM & carry) | (bitA & carry);
        *A = (*A & ~(1 << i)) | (sum << i);
    }
}

// Function to get 2's complement
int twosComplement(int num, int n) {
    return (~num + 1) & ((1 << n) - 1);
}

// Function to implement Booth's algorithm
void boothAlgorithm(int M, int Q, int n) {
    int A = 0; // Accumulator
    int Q_1 = 0; // Extra bit for Q
    int M_comp = twosComplement(M, n); // 2's complement of M
    int count = n;

    printf("Initial: A = %d, Q = %d, Q_1 = %d, M = %d, M_comp = %d\n", A, Q, Q_1, M, M_comp);

    while (count > 0) {
        int last_two = (Q & 1) | (Q_1 << 1);
        
        if (last_two == 1) { // 01: A = A + M
            add(&A, M, n);
            printf("Step %d: A + M, A = %d, Q = %d, Q_1 = %d\n", n-count+1, A, Q, Q_1);
        }
        else if (last_two == 2) { // 10: A = A - M
            add(&A, M_comp, n);
            printf("Step %d: A - M, A = %d, Q = %d, Q_1 = %d\n", n-count+1, A, Q, Q_1);
        }
        
        rightShift(&A, &Q, &Q_1, n);
        printf("Step %d: After right shift, A = %d, Q = %d, Q_1 = %d\n", n-count+1, A, Q, Q_1);
        
        count--;
    }

    // Combine A and Q to get the final result
    int result = (A << n) | (Q & ((1 << n) - 1));
    printf("Final result: %d\n", result);
}

int main() {
    int M, Q, n;

    printf("Enter the number of bits: ");
    scanf("%d", &n);
    printf("Enter multiplicand (M): ");
    scanf("%d", &M);
    printf("Enter multiplier (Q): ");
    scanf("%d", &Q);

    // Ensure numbers fit within n bits
    int max_val = (1 << (n-1)) - 1;
    int min_val = -(1 << (n-1));
    if (M > max_val || M < min_val || Q > max_val || Q < min_val) {
        printf("Error: Numbers exceed %d-bit range!\n", n);
        return 1;
    }

    boothAlgorithm(M, Q, n);
    return 0;
}
