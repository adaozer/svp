using namespace std;
using Vector = vector<double>;
using Basis = vector<Vector>;

Basis gram_schmidt(const Basis A);
Basis LLL(Basis A, const double S);