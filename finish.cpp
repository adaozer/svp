#include "finish.h"

double find_length(Vector u) { // Function finding the length of a vector u
    double result = 0; // Initialise result variable to zero, this will be returned as the length value.
    for (int i = 0; i < u.size(); ++i) {
        result = result + pow(u[i], 2); // Add the square of each dimension to result
    }
    return pow(result, 0.5); // Return the square root of the result
}

void write_to_file(double n) { // Function writing a float value onto a file
  ofstream result_file("result.txt"); // Create a file
  result_file << n; // Write the float n to the file
  result_file.close(); // Close the file
}

Basis arg_to_param(int argc, char* argv[]) { // Function turning the arguements into parameters with argc and argv as parameters.
    Basis basis; // Create the basis that will be created from the arguements.
    Vector vec; // Create a placeholder vector that will be added to basis each time a new vector is found in the arguements.
    for (int i = 1; i < argc; ++i) { // Parse the arguements
    string arg = argv[i];
    if (arg[0] == '[') { // Check if the arguement shows the start of a vector
        arg.erase(remove(arg.begin(), arg.end(), '['), arg.end()); // Remove the '[' character
        double argf = stof(arg); // Turn the string arg into a float
        vec.push_back(argf); // Push the number value to the placeholder vector.
    } else if (arg.back() == ']') { // Check if the arguement shows the end of a vector
        arg.erase(remove(arg.begin(), arg.end(), ']'), arg.end()); // Remove the ']' character
        double argf = stof(arg); // Turn the string arg into a float
        vec.push_back(argf); // Push the number to the placeholder vector 
        basis.push_back(vec); // Push the placeholder vector to the basis
        vec.clear(); // Clear the placeholder vector for the next vector that will be added to the basis
    } else { // If the arguement isn't the start or end of any vector, simply add the values to the vector vec
        double argf = stof(arg);
        vec.push_back(argf);
    }
    }
    return basis; // Return the basis to be used as a parameter
    }
