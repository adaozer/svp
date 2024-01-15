#include "vector_functions.h"  // Import header

double inner_product(Vector u, Vector v) {  // Inner product function
    double counter = 0;  // Initialise a counter to return
    for (int i = 0; i < u.size(); ++i) {
        counter += u[i]*v[i];  // Add product of dimension to counter
    }
    return counter;
    }

Vector scalar_multiply(Vector u, double scalar) {  // Vector times scalar
    Vector result;  // Initialise a vector to return
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i] * scalar);  // Add dimension * scalar to result
    }
    return result;
}

Vector vector_subtraction(Vector u, Vector v) {  // Vector Subtraction function
    Vector result;  // Initialise vector to return
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i]-v[i]);  // Add dimension - dimension to result
    }
    return result;
}

Vector vector_add(Vector u, Vector v) {  // Vector addition function
    Vector result;  // Initialise result vector to return
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i]+v[i]);  // Add dimension + dimension to result
    }
    return result;
}
