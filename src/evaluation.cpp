//
// Created by Penguin on 12/5/23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <cstdio>
#include <chrono>
#include "poly.h"

struct inData{
    int f_0;
    std::vector<Z> g;
};
struct ansData{
    std::vector<Z> ans;
};

std::pair<inData, ansData> loadTestData(int idx){
    std::string inName = "./test-data/" + std::to_string(idx) + ".in";
    std::string ansFile = "./test-data/" + std::to_string(idx) + ".out";
    auto f = std::freopen(inName.c_str(),"r",stdin);
    int f_0;
    int n = 0;
    std::cin >> f_0 >> n;
    std::vector<Z> g(n), ans(n);
    for (int j = 0; j < n; ++j){
        std::cin >> g[j];
    }
    g[0] = 0;
    fclose(f);

//    f = std::freopen(ansFile.c_str(),"r",stdin);
//    for (int j = 0; j < n; ++j){
//        std::cin >> ans[j];
//    }
    fclose(f);

    return {inData({f_0, g}), ansData({ans})};
}

bool compare(Poly& output, Poly& expected){
    if (output.size() != expected.size())
        return false;
    for (int i = 0; i < output.size(); ++i){
        if (output[i].val() != expected[i].val())
            return false;
    }
    return true;
}

Poly algorithm2(int f_0, std::vector<Z>& g){
    Poly G(g);
    Poly A = Poly({1}) - G;
    int n = g.size();
    Poly B = f_0 * A.inv(n);
    return B;
}

Poly bruteForce(int f_0, std::vector<Z>& g){
    std::vector<Z> f(g.size(),0);
    f[0] = f_0;
    for (int i = 1; i < f.size(); ++i){
        Z tmp = 0;
        for (int j = 1; j <= i; ++j){
            tmp += f[i - j] * g[j];
        }
        f[i] = tmp;
    }
    return Poly(f);
}
void solveFx(int l,int r, std::vector<Z> &f, std::vector<Z> &w, std::vector<Z> &g) {
    if (l==r) {
        if (l != 0){
            f[l] = w[l];
        }
        return;
    }
    int mid = (l + r) / 2;
    solveFx(l, mid, f, w, g);
    Poly h(std::vector<Z>(r - l + 1));
    for (int i = 0; i <= mid - l;i++){
        h[i] = f[i+l];
    }
    std::vector<Z> gpart(g.begin(), g.begin() + r - l + 1);
    Poly g_tmp(gpart);
    Poly contribution = h * g_tmp;
    for (int i=mid + 1; i <= r; i++){
        w[i] += contribution[i - l];
    }
    solveFx(mid + 1, r, f, w, g);
}

std::vector<Z> divide_and_conquer(int f_0, std::vector<Z> &g) {
    std::vector<Z> w(g.size());
    std::vector<Z> f(g.size());
    f[0] = f_0;
    solveFx(0, g.size(), f, w, g);
    return f;
}

double judge1(int idx){
    std::pair<inData, ansData> data = loadTestData(idx);
    Poly ans = data.second.ans;

    auto startTime = std::chrono::high_resolution_clock::now();

    Poly out = divide_and_conquer(data.first.f_0, data.first.g);

    auto endTime = std::chrono::high_resolution_clock::now();

    if (!compare(out, ans) and false){
        std::cout<<"[Test Point "+std::to_string(idx)+"] Wrong Answer.\n";
    }

    std::chrono::duration<double, std::milli> runTime = endTime - startTime;
    return runTime.count();
}

double judge2(int idx){
    std::pair<inData, ansData> data = loadTestData(idx);
    Poly ans = data.second.ans;

    auto startTime = std::chrono::high_resolution_clock::now();

    Poly out = algorithm2(data.first.f_0, data.first.g);

    auto endTime = std::chrono::high_resolution_clock::now();

    if (!compare(out, ans) and false){
        std::cout<<"[Test Point "+std::to_string(idx)+"] Wrong Answer.\n";
    }

    std::chrono::duration<double, std::milli> runTime = endTime - startTime;
    //std::cout << "[Test Point "+std::to_string(idx)+"] Accepted. Runtime: " << runTime.count() << "ms\n";
    return runTime.count();
}

double judgeBF(int idx){
    std::pair<inData, ansData> data = loadTestData(idx);
    Poly ans = data.second.ans;

    auto startTime = std::chrono::high_resolution_clock::now();

    Poly out = bruteForce(data.first.f_0, data.first.g);

    auto endTime = std::chrono::high_resolution_clock::now();

    if (!compare(out, ans) and false){
        std::cout<<"[Test Point "+std::to_string(idx)+"] Wrong Answer.\n";
    }

    std::chrono::duration<double, std::milli> runTime = endTime - startTime;
    //std::cout << "[Test Point "+std::to_string(idx)+"] Accepted. Runtime: " << runTime.count() << "ms\n";
    return runTime.count();
}

int main(){
    double accu_time = 0;
    int idx = 0;
    std::vector<int> stages = {100, 100, 20, 10, 5, 3, 1, 1};
    std::vector<int> n = {5, 20, 100, 1000, 5000, 10000, 50000, 100000};
    std::ofstream outFile("./Algorithm 1 Runtime.txt");
    for (int i = 0; i < stages.size(); ++i){
        //printf("Stage %d\n", i);
        for (int test = 0; test < stages[i]; ++test, ++idx){
            printf("idx = %d\n", idx);
            accu_time += judge1(idx);
        }
        accu_time /= stages[i];
        outFile << "Stage " << i << ". Poly Size: " << n[i] << ". Time:" << accu_time << "ms\n";
        accu_time = 0;
    }
    outFile.close();
}
