#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
using Vector = vector<double>;
using Basis = vector<Vector>;

double inner_product(const Vector u, const Vector v){

    double counter = 0;
    for (int i = 0; i<u.size(); ++i){
        counter += u[i]*v[i];
    } 
    return counter;
    }

Vector scalar_multiply(const Vector u, const double scalar) {
    
    Vector result;
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i] * scalar);
    }
    return result;
}

void print_vector(Vector v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

void print_matrix(Basis mat){
    for (const auto& row : mat) {
        for (auto elem : row) {
            cout << elem << ' ';
        }
        cout << '\n';
    }
}

Vector vector_subtraction(const Vector u, const Vector v) {
    Vector result;
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i]-v[i]);
    }
    return result;
}

Vector vector_add(const Vector u, const Vector v) {
    Vector result;
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i]+v[i]);
    }
    return result;
}

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

Basis LLL(Basis As, double S=0.75) {
    Basis A = As; // Buraya sonra kesin bak
    Basis B = gram_schmidt(A);
    int n = B.size();
    Basis mu(n, Vector(n,0)); // Bu ne aw
    for (int i = 0; i < n; ++i){
        for (int j = 0; j <= i; ++j) { // Buraya sonra bi bak
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
                for (int i = 0; i < k+1; ++i) {
                    for (int p = 0; p <= i; ++p) {
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
            for (int i = 0; i < k+1; ++i) {
                for (int g = 0; g <= i; ++g) {
                    mu[i][g] = inner_product(A[i], B[g])/inner_product(B[g], B[g]);
                }
            }
            k = max(k-1, 1);
        }
    }
    return A;
}

int main(){
    Vector u = {1,2,3};
    Basis v = {{1, 1}, {1, 0}};
    Basis g = {{1, 2, 2}, {2, -1, 1}, {3, 0, 1}};
    Basis c = {{3, 1, 1}, {-1, 2, 4}, {2, 0, 3}};
    Basis deneme = {{201, 37}, {1648,297}};
    print_matrix(LLL(deneme));
    print_matrix(LLL(v));
    print_matrix(LLL(g));
    print_matrix(LLL(c));
    return 0;
}

