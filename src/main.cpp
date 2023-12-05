#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "poly.h"
#include <cmath>

using namespace std;

int main() {

    int f_0 = 1;
    vector<Z> a = {0, 3, 4, 4};

    Poly G(a);
    Poly A = Poly({1}) - G; // 1 - G

    int n = 4;
    // n = (int) pow(2, (int) ceil(log2(n)));

    Poly B = f_0 * A.inv(n); // {1, 3, 13, 55}

    printPolynomial(B);
    return 0;
}
