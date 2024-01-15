#include "svp.h"
#include <sstream>
#include <string>
#include <algorithm>

Basis parseArguments(int argc, char* argv[]) {
    Basis lattice;
    string combinedArg;
    bool isCombining = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg.front() == '[') {
            combinedArg = arg;
            isCombining = true;
        } else if (arg.back() == ']') {
            combinedArg += " " + arg;
            isCombining = false;

            combinedArg.erase(remove(combinedArg.begin(), combinedArg.end(), '['), combinedArg.end());
            combinedArg.erase(remove(combinedArg.begin(), combinedArg.end(), ']'), combinedArg.end());

            istringstream ss(combinedArg);
            Vector latticeVector;
            double value;
            while (ss >> value) {
                latticeVector.push_back(value);
            }

            lattice.push_back(latticeVector);
            combinedArg.clear();
        } else if (isCombining) {
            combinedArg += " " + arg;
        }
    }

    return lattice;
}

int main(int argc, char* argv[]){

    if (argc < 3) {
        cout << "Wrong input \n";
        return 1;
    } else {
    Basis A = parseArguments(argc, argv);
    A = LLL(A);
    double r = pow(inner_product(A[0],A[0]), 0.5);
    Vector B = schnorr_euchner(A, r);
    double n = find_length(B);
    write_to_file(n);
    return 0;
    }
    }
