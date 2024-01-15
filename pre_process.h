#include <cmath>
#include "vector_functions.h"

using Basis = vector<Vector>;

Basis gram_schmidt(Basis A); 
Basis LLL(Basis A, double S=0.75);
