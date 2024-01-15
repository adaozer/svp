#include "finish.h"
#include <stdexcept>

double find_length(Vector u) {  // Function finding the length of a vector u
    double result = 0;  // Initialise result variable to zero to be returned
    for (int i = 0; i < u.size(); ++i) {
        result = result + pow(u[i], 2);  // Add dimension squared to result
    }
    return pow(result, 0.5);  // Return the square root of the result
}

void write_to_file(double n) {  // Function writing a float value onto a file
  ofstream result_file("result.txt");  // Create a file
  result_file << n;  // Write the float n to the file
  result_file.close();  // Close the file
}

Basis arg_to_param(int argc, char* argv[]) {  // argument to parameter function
    Basis basis;  // Create the basis that will be created from the arguments.
    Vector vec;  // Placeholder vector to push into basis later
    for (int i = 1; i < argc; ++i) {  // Parse the arguments
    string arg = argv[i];
    if (arg[0] == '[') {  // Check if the argument shows the start of a vector
        arg.erase(remove(arg.begin(), arg.end(), '['), arg.end());  // Remove [
        try {
        double argf = stof(arg);  // Turn the string arg into a float
        vec.push_back(argf);  // Push  number value to placeholder vector.
        } catch (exception& e) {  // Catch exceptions
            Basis fail;
            return fail;  // Return empty basis
        }
    } else if (arg.back() == ']') {  // Check if argument shows end of a vector
        arg.erase(remove(arg.begin(), arg.end(), ']'), arg.end());  // Remove ]
        try {
        double argf = stof(arg);  // Turn the string arg into a float
        vec.push_back(argf);  // Push the number to the placeholder vector
        basis.push_back(vec);  // Push the placeholder vector to the basis
        vec.clear();  // Empty placeholder vector for next loop iteration
        } catch (exception& e) {  // Catch exceptions
            Basis fail;
            return fail;  // Return empty basis
        }
    } else {  // If arg doesn't have [ or ], simply add arg to vec
        try {
        double argf = stof(arg);
        vec.push_back(argf);
        } catch (exception& e) {  // Catch exceptions
            Basis fail;
            return fail;  // Return empty basis
        }
    }
    }
    return basis;  // Return the basis to be used as a parameter
    }
