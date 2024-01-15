#include "pre_process.h"

Basis gram_schmidt(Basis A) {  // Gram schmidt function for finding orthobasis
    Basis B;
    B.push_back(A[0]);  // Initialise orthobasis B
    for (int i = 1; i < A.size(); ++i) {  // Parse the remaining vectors in A
        int counter = 0;  // Initialise counter to zero to iterate
        Basis hats;  // Initialise a basis for the projection vectors.
        while (counter < i) {
            double hat_top = inner_product(A[i], B[counter]);
            double hat_bottom = inner_product(B[counter], B[counter]);
            if (hat_bottom > 0.000001) {
            Vector hat_final = scalar_multiply(B[counter], hat_top/hat_bottom);
            // Calculate projection vectors
            hats.push_back(hat_final);  // Push projections to basis
            counter++;  // Progress the loop after vectors are calculated.
            } else { // Check for division by 0
                Basis fail;
                return fail; // Return empty basis
            }
        }
        Vector result = A[i];  // Initialise result for the projection vectors.
        for (int z = 0; z < hats.size(); ++z) {
            result = vector_subtraction(result, hats[z]);
            // Parse hats basis and subtract vectors from each other.
        }
        bool add = false; // Check for all 0 vector
        for (int i = 0; i < result.size(); ++i) {
            if (result[i] > 0.000001) {
                add = true;
            }
        }
        if (add) {
        B.push_back(result);  // Put the resulting vector in the orthobasis.
        } else { // Check for all 0 vector
            Basis fail;
            return fail;
        }
    }
    return B;  // Return the orthobasis.
}

Basis LLL(Basis A, double S) {  // LLL function returning LLL-reduced basis
    Basis B = gram_schmidt(A);  // Find the orthobasis of the basis
    if (B.empty()) { // Check for exception
        return B;
    }
    int n = B.size();  // Initialise a size variable
    Basis mu(n, Vector(n, 0));  // Create the mu matrix
    for (int i = 0; i < n; ++i) {  // Fill in the mu matrix
        for (int j = 0; j < mu[i].size(); ++j) {
            mu[i][j] = inner_product(A[i], B[j])/inner_product(B[j], B[j]);
        }
    }

    int k = 1;  // Initialise the k variable for looping
    while (k < n) {
        for (int j = k-1; j > -1; --j) {
            if (abs(mu[k][j]) > 0.5) {
                Vector tempp = scalar_multiply(A[j], round(mu[k][j]));
                A[k] = vector_subtraction(A[k], tempp);  // Find new A[k] value
                B = gram_schmidt(A);  // Recalculate gram scmidt process
                for (int i = 0; i < n; ++i) {  // Reinitialise mu
                    for (int p = 0; p < mu[i].size(); ++p) {
                        double mu_first = inner_product(A[i], B[p]);
                        mu[i][p] = mu_first/inner_product(B[p], B[p]);
                    }
                }
            }
        }
        double B_ = inner_product(B[k], B[k]);
        double B__ = inner_product(B[k-1], B[k-1]);
        if (B_ > (S-(pow((mu[k][k-1]), 2))) * B__) {  // Check Lovasz condition
            k++;  // Progress the loop
        } else {
            swap(A[k], A[k-1]);  // Swap A[k] and A[k-1]
            B = gram_schmidt(A);  // Recalculate the gram schmidt process
            for (int i = 0; i < n; ++i) {  // Reinitialise mu
                for (int g = 0; g < mu[i].size(); ++g) {
                    double mu_first = inner_product(A[i], B[g]);
                    mu[i][g] = mu_first/inner_product(B[g], B[g]);
                }
            }
            k = max(k-1, 1);
        }
    }
    return A;  // Return the reduced basis
}
