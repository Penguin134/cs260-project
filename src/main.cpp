#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "poly.h"
#include <cmath>

using namespace std;

int main() {

    int f_0 = 1;
    Poly G({0, 3, 4, 4});
    Poly A = Poly({1}) - G; // 1 - G

    int n = 3;
    n = (int) pow(2, (int) ceil(log2(n)));

    Poly B = f_0 * A.inv(n); // {1, 3, 13, 55}

    printPolynomial(B);
    return 0;
}
