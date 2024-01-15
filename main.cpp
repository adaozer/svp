#include "finish.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Wrong input \n";
        return 1;
    } else {
    Basis A = parseArguments(argc, argv);
    A = LLL(A);
    double r = pow(inner_product(A[0], A[0]), 0.5);
    Vector B = schnorr_euchner(A, r);
    double n = find_length(B);
    write_to_file(n);
    return 0;
    }
    }
