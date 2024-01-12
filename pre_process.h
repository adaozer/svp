#include <cmath> // Eğer bunu svpde kullanmazsam (ki sanmıyorum) o zaman kaldırılıp pre_process.cpp'ye taşınacak.
#include "vector_functions.h"

using Basis = vector<Vector>;

Basis gram_schmidt(const Basis A);
Basis LLL(Basis A, const double S);