#include "svp.h"

Vector schnorr_euchner(Basis A, double r) {  // Schnorr-Euchner enumeration
    Basis B = gram_schmidt(A);  // Calculate the orthobasis of A
    int n = A.size();  // Initialise size variable
    Basis mu(n, Vector(n, 0));  // Initialise mu basis
    Vector B_inner;  // Initialise the array of orthobasis norms
    Vector p(n + 1, 0);  // Initialise the p, v, c, w arrays
    Vector v(n, 0);
    v[0] = 1;
    Vector c(n, 0);
    Vector w(n, 0);
    int k = 0;  // Initialise k variable for parsing
    int last_nonzero = 0;  // Initialise last_nonzero variable for looping
    double R_squared = pow(r, 2);  // Calculate radius squared
    Vector s = A[0];  // Initialise the result vector s
    for (int i=0; i < B.size(); ++i) {  // Fill up orthobasis norm array
        B_inner.push_back(inner_product(B[i], B[i]));
    }
    for (int i = 0; i < n; ++i) {  // Fill up mu matrix
        for (int j = 0; j < mu[i].size(); ++j) {
            mu[i][j] = inner_product(A[i], B[j])/inner_product(B[j], B[j]);
        }
    }

    while (1) {
        p[k] = p[k+1] + pow((v[k] + c[k]), 2) * B_inner[k];
        // Check Schnorr-Euchner condition
        if (p[k] < R_squared) {
            if (k == 0) {
                R_squared = p[k];
                s = Vector(A[0].size(), 0);  // Initialise s to be 0
                // Calculate the result of the sigma to find s
                for (int i = 0; i < n; ++i) {
                    s = vector_add(scalar_multiply(A[i], v[i]), s);
                }
            } else {
                --k;
                c[k] = 0;  // Initialise c[k] to be 0
                // Calculate the result of the sigma to find c[k]
                for (int i = k+1; i < n; ++i) {
                    c[k] = c[k] + mu[i][k] * v[i];
                }
                c[k] = -c[k];  // Calculate -sigma
                v[k] = round(c[k]);
                w[k] = 1;
            }
        } else {
            ++k;
            if (k == n) {
                return s;  // Return shortest vector s
            }
            // Check conditions and increment each variable per the algorithm
            if (k >= last_nonzero) {
                last_nonzero = k;
                ++v[k];
            } else {
                if (v[k] > c[k]) {
                    v[k] = v[k] - w[k];
                } else {
                    v[k] = v[k] + w[k];
                }
                ++w[k];
            }
        }
    }
}
