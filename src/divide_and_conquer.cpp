#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>

#include "poly.h"

using namespace std;

void solveFx(int l,int r, vector<Z> &f, vector<Z> &w, vector<Z> &g) {
    if (l==r) {
        if (l != 0){
            f[l] = w[l];
        }
        return;
    }
    int mid = (l + r) / 2;
    solveFx(l, mid, f, w, g);
    Poly h(vector<Z>(r - l + 1));
    for (int i = 0; i <= mid - l;i++){
        h[i] = f[i+l];
    }
    vector<Z> gpart(g.begin(), g.begin() + r - l + 1);
    Poly g_tmp(gpart);
    Poly contribution = h * g_tmp;
    for (int i=mid + 1; i <= r; i++){
        w[i] += contribution[i - l];
    }
    solveFx(mid + 1, r, f, w, g);
}

vector<Z> divide_and_conquer(int f_0, vector<Z> &g) {
    vector<Z> w(g.size());
    vector<Z> f(g.size());
    f[0] = f_0;
    solveFx(0, g.size(), f, w, g);
    return f;
}

int main(){
    int f_0 = 1;
    vector<Z> G({0, 3, 4, 4});
    vector<Z> result = divide_and_conquer(f_0, G);
    for (auto i: result){
        cout << i << " ";
    }
    cout <<endl;
}