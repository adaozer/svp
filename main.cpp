#include "svp.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

Basis parseArguments(int argc, char* argv[]) {
    Basis lattice;
    string combArg;
    bool isCombining = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg.front() == '[') {
            combArg = arg;
            isCombining = true;
        } else if (arg.back() == ']') {
            combArg += " " + arg;
            isCombining = false;

            auto rem_start = remove(combArg.begin(), combArg.end(), '[');
            combArg.erase(rem_start, combArg.end());

            auto rem_end = remove(combArg.begin(), combArg.end(), ']');
            combArg.erase(rem_end, combArg.end());

            istringstream ss(combArg);
            Vector latticeVector;
            double value;
            while (ss >> value) {
                latticeVector.push_back(value);
            }

            lattice.push_back(latticeVector);
            combArg.clear();
        } else if (isCombining) {
            combArg += " " + arg;
        }
    }

    return lattice;
    }

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Wrong input \n";
        return 1;
    } else {
    Basis A = parseArguments(argc, argv);
    A = LLL(A);
    double r = pow(inner_product(A[0], A[0]), 0.5);
    Vector B = schnorr_euchner(A, r);
    double n = find_length(B);
    write_to_file(n);
    return 0;
    }
    }
