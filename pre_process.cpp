#include "pre_process.h"

Basis gram_schmidt(Basis A) { // Gram schmidt function which takes as input a basis and returns the orthobasis of said basis.
    Basis B;
    B.push_back(A[0]); // Initialise an orthobasis B and push the first A vector into it, as that vector will be returned as is.
    for (int i = 1; i < A.size(); ++i) { // Parse the remaining vectors in A
        int counter = 0; // Initialise a counter to 0, this will be used for each projection
        Basis hats; // Initialise another basis which will include all the projection vectors.
        while (counter < i) {
            double hat_top = inner_product(A[i], B[counter]); 
            double hat_bottom = inner_product(B[counter], B[counter]);
            Vector hat_final = scalar_multiply(B[counter], hat_top/hat_bottom); // Calculate each projection vector step by step.
            hats.push_back(hat_final); // After calculating, push them onto the projection basis to subtract from each other to find the final vector.
            counter++; // Progress the loop after each vector has been calculated.
        }
        Vector result = A[i]; // Initialise the result of the projection vector. The subtraction will be done starting from the original vector, hence it is the current value.
        for (int z = 0; z < hats.size(); ++z) {
            result = vector_subtraction(result, hats[z]); // Parse the projection vectors basis and subtract the vectors from each other.
        }
        B.push_back(result); // Put the resulting vector in the orthobasis.
    }
    return B; // Return the orthobasis.
}

Basis LLL(Basis A, double S) { // LLL function taking the basis that will be reduced and the delta value for the Lovasz condition as parameters
    Basis B = gram_schmidt(A); // Find the orthobasis of the basis
    int n = B.size(); // Initialise a size variable
    Basis mu(n, Vector(n, 0)); // Create the mu matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < mu[i].size(); ++j) {
            mu[i][j] = inner_product(A[i], B[j])/inner_product(B[j], B[j]); // Fill in the mu matrix
        }
    }

    int k = 1; // Initialise the k variable for looping
    while (k < n) {
        for (int j = k-1; j > -1; --j) {
            if (abs(mu[k][j]) > 0.5) {
                Vector tempp = scalar_multiply(A[j], round(mu[k][j])); // Split operation up for easier reading
                A[k] = vector_subtraction(A[k], tempp); // Calculate a new A[k] value
                B = gram_schmidt(A); // Recalculate gram scmidt process
                for (int i = 0; i < n; ++i) {
                    for (int p = 0; p < mu[i].size(); ++p) {
                        double mu_first = inner_product(A[i], B[p]);
                        mu[i][p] = mu_first/inner_product(B[p], B[p]); // Reinitialise mu
                    }
                }
            }
        }
        double B_ = inner_product(B[k], B[k]);
        double B__ = inner_product(B[k-1], B[k-1]); // Split the operation up for easier reading
        if (B_ > (S-(pow((mu[k][k-1]), 2))) * B__) { // Check Lovasz condition
            k++; // Progress the loop if the Lovasz condition has been met
        } else {
            swap(A[k], A[k-1]); // Swap A[k] and A[k-1]
            B = gram_schmidt(A); // Recalculate the gram schmidt process
            for (int i = 0; i < n; ++i) {
                for (int g = 0; g < mu[i].size(); ++g) {
                    double mu_first = inner_product(A[i], B[g]);
                    mu[i][g] = mu_first/inner_product(B[g], B[g]); // Reinitialise mu
                }
            }
            k = max(k-1, 1);
        }
    }
    return A; // Return the reduced basis
}
