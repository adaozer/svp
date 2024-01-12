#include <iostream>
#include <vector>
#include "pre_process.h"

using namespace std;
using Vector = vector<double>;
using Basis = vector<Vector>;

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
    Vector u = {1,2,3};
    Basis v = {{1, 1}, {1, 0}};
    Basis g = {{1, 2, 2}, {2, -1, 1}, {3, 0, 1}};
    Basis c = {{3, 1, 1}, {-1, 2, 4}, {2, 0, 3}};
    Basis deneme = {{201, 37}, {1648,297}};
    print_matrix(LLL(g, 0.75));
    return 0;
}
