#include "svp.h"

Basis schnorr_euchner(Basis A, double r) {
    int n = A.size();
    Basis mu(n, Vector(n,0)); 
    Basis B = gram_schmidt(A);

    return A;
}
