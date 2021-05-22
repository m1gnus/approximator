#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int** read_matrix_from_file(const char* filename, size_t* n, size_t* m) {
    FILE* fd = fopen(filename, "r");

    size_t i, j;
    fscanf(fd, "%zu", n); fscanf(fd, "%zu", m);

    int** matrix = malloc(*n * sizeof(int*));
    for (i=0; i<*n; i++) {
        matrix[i] = malloc(*m * sizeof(int));
        for (j=0; j<*m; j++) {
            fscanf(fd, "%d", (matrix[i] + j));
        }
    }

    return matrix;
}

int resolve_sbox(int** sbox, size_t m, int input) {
    return sbox[input/m][(input%m)];
}

int** calc_linear_approx_table(int** matrix, size_t n, size_t m) {
    size_t i, j, k, approx_size = n * m;

    int** linear_approx_table = malloc(approx_size * sizeof(int*));
    int mean = approx_size / 2, zeros, input, output;
    for (i=0; i<approx_size; i++) {
        linear_approx_table[i] = malloc(approx_size * sizeof(int));
        for (j=0; j<approx_size; j++) {
            zeros = 0;
            for (k=0; k<approx_size; k++) {
                input = k;
                output = resolve_sbox(matrix, m, input);
                if (!((xor_int(input & i)) ^ (xor_int(output & j)))) {
                    zeros++;
                }
            }
            zeros -= mean;
            linear_approx_table[i][j] = zeros;
        }
    }

    return linear_approx_table;
}

int xor_int(int input) {
    int acc = 0;
    while (input) {
        acc ^= input & 1;
        input >>= 1;
    }
    return acc;
}

void print_matrix(int** matrix, size_t n, size_t m) {
    size_t i, j;

    for (i=0; i<n; i++) {
        printf("+");
        for (j=0; j<m; j++) printf("----+");
        puts("");
        for (j=0; j<m; j++) printf("|%3d ", matrix[i][j]);
        printf("|\n");
    }
    printf("+");
    for (j=0; j<m; j++) printf("----+");
    puts("");
    fflush(stdout);
}

void usage(char* call_name) {
    printf("Usage: %s <path>\n", call_name);
}
