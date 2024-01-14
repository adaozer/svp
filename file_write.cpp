#include "file_write.h"

double find_length(Vector u) {
    double result = 0;
    for (int i = 0; i < u.size(); ++i) {
        result = result + pow(u[i],2);
    }
    return pow(result, 0.5);
}

void write_to_file(double n) {

  ofstream result_file("result.txt");

  result_file << n;

  result_file.close();
  
}
