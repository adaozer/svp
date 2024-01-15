#include "vector_functions.h"

double inner_product(Vector u, Vector v){

    double counter = 0;
    for (int i = 0; i<u.size(); ++i){
        counter += u[i]*v[i];
    } 
    return counter;
    }

Vector scalar_multiply(Vector u, double scalar) {
    
    Vector result;
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i] * scalar);
    }
    return result;
}

Vector vector_subtraction(Vector u, Vector v) {
    Vector result;
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i]-v[i]);
    }
    return result;
}

Vector vector_add(Vector u, Vector v) {
    Vector result;
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i]+v[i]);
    }
    return result;
}
