#include "svp.h"

Vector schnorr_euchner(Basis A, double r) {
    Basis B = gram_schmidt(A);
    int n = A.size();
    Basis mu(n, Vector(n,0));
    Vector B_inner;
    Vector p(n + 1, 0);
    Vector v(n, 0);
    v[0] = 1;
    Vector c(n, 0);
    Vector w(n, 0);
    int k = 0;
    int last_nonzero = 0;
    double R_squared = pow(r, 2);
    Vector s = A[0];
    for (int i=0; i < B.size(); ++i) {
        B_inner.push_back(inner_product(B[i], B[i]));
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < mu[i].size(); ++j) {
            mu[i][j] = inner_product(A[i], B[j])/inner_product(B[j], B[j]);
        }
    }

    while (1) {
        p[k] = p[k+1] + pow((v[k] + c[k]),2) * B_inner[k];

        if (p[k] < R_squared) {
            if (k==0) {
                R_squared = p[k];
                s = Vector(A[0].size(), 0);
                for(int i = 0; i < n; ++i) {
                    s = vector_add(scalar_multiply(A[i], v[i]), s);
                }
            } else {
                --k;
                c[k] = 0;
                for (int i = k+1; i < n; ++i) {
                    c[k] = c[k] + mu[i][k] * v[i];
                }
                c[k] = -c[k];
                v[k] = round(c[k]);
                w[k] = 1;
            }
        
        } else {
            ++k;
            if (k==n) {
                return s;
            } 
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