#include "finish.h" // Import finish to use
#include <iostream> // Import iostream as cout will be used

int main(int argc, char* argv[]) {  
    if (argc < 3) { // Check the amount of arguements
        cout << "Wrong input\nThere must be at least 2 vectors in the basis.\n"; // If there aren't enough arguements print
        return 1; // Exit with error
    }
    Basis A = arg_to_param(argc, argv); // Initialise parameters.
    if (A.empty()) {
        cout << "Wrong input format.\nCorrect format is [x y z] [a b c]...\n"; // If the parameters are wrong; input format is wrong print
        return 1; // Exit with error
    }
    Basis B = LLL(A); // Calculate LLL of the basis
    double r = pow(inner_product(B[0], B[0]), 0.5); // Calculate the radius of the basis
    Vector C = schnorr_euchner(B, r); // Calculate the svp
    double n = find_length(C); // Find the length of the shortest vector
    write_to_file(n); // Write it onto a file
    return 0; // Exit successfully
    }
