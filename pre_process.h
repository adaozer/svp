#include <cmath>  // Include cmath for power, absolute value, rounding functions
#include "vector_functions.h"  // Include the previous simple vector functions for use in this file

using Basis = vector<Vector>;  // Define a basis, a vector made out of other float containing vectors for easier use

Basis gram_schmidt(Basis A);  // Define the gram schmidt and LLL functions for pre processing the inputted basis.
Basis LLL(Basis A, double S=0.75);
