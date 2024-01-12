#include "vector_functions.h"

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
