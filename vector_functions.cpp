#include "vector_functions.h" // Import header

double inner_product(Vector u, Vector v) { // Function for finding the inner product of 2 vectors, taking 2 vectors as the parameter.
    double counter = 0; // Initialise a counter; this is what we will be returning as the result.
    for (int i = 0; i < u.size(); ++i) {
        counter += u[i]*v[i]; // Add the product of each vector dimension to the counter variable.
    }
    return counter;
    }

Vector scalar_multiply(Vector u, double scalar) { // Function for multiplying a vector with a scalar, taking in a vector and a scalar to multiply as the parameter.
    Vector result; // Initialise a vector, this will be what we will be returning as the final vector.
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i] * scalar); // Times each dimensions of the input vector with the input scalar. Push the result onto the new result vector.
    }
    return result;
}

Vector vector_subtraction(Vector u, Vector v) { // Vector Subtraction function taking 2 vectors to subtract as the parameter.
    Vector result; // Initialise vector which we will be returning as the final vector.
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i]-v[i]); // Subtract each dimension of the 2 vectors, and push the final answer onto the result vector.
    }
    return result;
}

Vector vector_add(Vector u, Vector v) { // Vector addition function taking 2 vectors to add as the parameter.
    Vector result; // Initialise result vector to push the added dimensions into.
    for (int i = 0; i < u.size(); ++i) {
        result.push_back(u[i]+v[i]); // Add each dimension of the 2 vectors and push them onto result to return.
    }
    return result;
}
