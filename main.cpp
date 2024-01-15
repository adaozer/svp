#include "finish.h"  // Import finish to use
#include <iostream>  // Import iostream as cout will be used

int main(int argc, char* argv[]) {
    if (argc < 3) {  // Check the amount of arguments
        cout << "Wrong input\n";
        return 1;  // Exit with error if not enough arguments
    }
    Basis A = arg_to_param(argc, argv);  // Initialise parameters.
    if (A.empty()) {
        cout << "Wrong input format.\nCorrect format: [x y z] [a b c]...\n";
        return 1;  // Exit with error if wrong input format
    } else if (A.size() == 1) { // Check the amount of vectors in basis
        cout << "Wrong input\nThere must be at least 2 vectors in the basis\n";
    }
    Basis B = LLL(A);  // Calculate LLL of the basis
    double r = pow(inner_product(B[0], B[0]), 0.5);  // Find radius of lattice
    Vector C = schnorr_euchner(B, r);  // Calculate the svp
    double n = find_length(C);  // Find the length of the shortest vector
    write_to_file(n);  // Write it onto a file
    return 0;  // Exit successfully
    }
