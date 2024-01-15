#include <fstream>
#include <algorithm>
#include <string>
#include "svp.h"

double find_length(Vector u);
void write_to_file(double n);
Basis parseArguments(int argc, char* argv[]);