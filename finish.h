#include <fstream> // fstream for writing to file
#include <algorithm> 
#include <string> // String and algorithm for turning arguements to parameters
#include "svp.h" // Import the previous functions for use.

double find_length(Vector u); // Define each of the finishing variables after finding the shortest vector.
void write_to_file(double n);
Basis arg_to_param(int argc, char* argv[]);