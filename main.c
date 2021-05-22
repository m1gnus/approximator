#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "err.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        usage(argv[0]);
        return ERR_BADARGS;
    }

    const char* filename = argv[1];
    size_t n, m;
    int **sbox = read_matrix_from_file(filename, &n, &m), **linear_approx_table;
    printf("\n========== printing sbox as a %zu x %zu matrix\n\n", n, m);
    print_matrix(sbox, n, m);
    linear_approx_table = calc_linear_approx_table(sbox, n, m);
    printf("\n========== printing linear approximation table as a square matrix of size %zu\n\n", n*m);
    print_matrix(linear_approx_table, n*m, n*m);

    return SUCCESS;
}
