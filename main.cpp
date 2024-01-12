#include <iostream>
#include "svp.h"

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

int main(){
    Basis A = {{2,2,1},{4,3,1}};
    Basis pre_process = LLL(A, 0.75);
    print_matrix(pre_process);
    //print_matrix(schnorr_euchner(pre_process, 10));
    return 0;
}
