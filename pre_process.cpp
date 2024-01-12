#include "pre_process.h"

Basis gram_schmidt(const Basis A){
    Basis B;
    B.push_back(A[0]);

    for (int i = 1; i < A.size(); ++i){
        int counter = 0;
        Basis hats;
        while (counter < i) {
            double hat_top = inner_product(A[i], B[counter]);
            double hat_bottom = inner_product(B[counter], B[counter]);
            if (hat_bottom != 0){
            Vector hat_final = scalar_multiply(B[counter], hat_top/hat_bottom);
            hats.push_back(hat_final);
            }
            counter++;
        } 
        Vector result = A[i];
        for (int z = 0; z < hats.size(); ++z) {
            result = vector_subtraction(result, hats[z]);
        }
        B.push_back(result);
    }
    return B;
}

Basis LLL(Basis A, const double S) {
    Basis B = gram_schmidt(A);
    int n = B.size();
    Basis mu(n, Vector(n,0)); // Bu ne aw
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < mu[i].size(); ++j) {
            mu[i][j] = inner_product(A[i], B[j])/inner_product(B[j], B[j]);
        }
    }

    int k = 1;
    while (k < n) {
        for (int j = k-1; j > -1; --j) {
            if (abs(mu[k][j]) > 0.5) {
                Vector tempp = scalar_multiply(A[j], round(mu[k][j]));
                A[k] = vector_subtraction(A[k], tempp);
                B = gram_schmidt(A);
                for (int i = 0; i < n; ++i) {
                    for (int p = 0; p < mu[i].size(); ++p) {
                        mu[i][p] = inner_product(A[i], B[p])/inner_product(B[p],B[p]);
                    }
                
                }

            }
        }
        if (inner_product(B[k], B[k]) > (S-(pow((mu[k][k-1]),2))) * inner_product(B[k-1], B[k-1])){
            k++;
        }
        else {
            swap(A[k], A[k-1]);
            B = gram_schmidt(A);
            for (int i = 0; i < n; ++i) {
                for (int g = 0; g < mu[i].size(); ++g) {
                    mu[i][g] = inner_product(A[i], B[g])/inner_product(B[g], B[g]);
                }
            }
            k = max(k-1, 1);
        }
    }
    return A;
}