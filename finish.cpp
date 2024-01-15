#include "finish.h"

double find_length(Vector u) {
    double result = 0;
    for (int i = 0; i < u.size(); ++i) {
        result = result + pow(u[i], 2);
    }
    return pow(result, 0.5);
}

void write_to_file(double n) {
  ofstream result_file("result.txt");
  result_file << n;
  result_file.close();
}

Basis parseArguments(int argc, char* argv[]) {
    Basis basis;
    Vector vec;
    for (int i = 1; i < argc; ++i) {
    string arg = argv[i];
    if (arg[0] == '[') {
        arg.erase(remove(arg.begin(), arg.end(), '['), arg.end());
        double argf = stof(arg);
        vec.push_back(argf);
    } else if (arg.back() == ']') {
        arg.erase(remove(arg.begin(), arg.end(), ']'), arg.end());
        double argf = stof(arg);
        vec.push_back(argf);
        basis.push_back(vec);
        vec.clear();
    } else {
        double argf = stof(arg);
        vec.push_back(argf);
    }
    }
    return basis;
    }
