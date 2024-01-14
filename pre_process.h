#include <cmath>
#include "vector_functions.h"

using Basis = vector<Vector>;

Basis gram_schmidt(const Basis A); 
Basis LLL(Basis A, const double S);