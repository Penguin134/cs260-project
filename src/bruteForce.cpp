#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <cstdio>

std::vector<long long> bruteForce(long long f_0, std::vector<long long>& g){
    std::vector<long long> f(g.size(),0);
    f[0] = f_0;
    for (int i = 1; i < f.size(); ++i){
        long long tmp = 0;
        for (int j = 1; j <= i; ++j){
            tmp += f[i - j] * g[j];
        }
        f[i] = tmp;
    }
    return f;
}

int main(){
//    long long f_0 = 1, n = 20;
//    std::vector<long long> g(n, 1);
//    std::vector<long long> ans = bruteForce(f_0, g);
//    for (int j = 0; j < ans.size(); ++j){
//        std::cout << std::to_string(ans[j]) + " ";
//    }
//    return 0;
    for (int i = 0; i < 1000; ++i){
        std::string inName = "./test-data/" + std::to_string(i) + ".in";
        std::string outName = "./test-data/" + std::to_string(i) + ".out";
        std::freopen(inName.c_str(),"r",stdin);
        std::freopen(outName.c_str(),"w",stdout);

        long long f_0, n;
        std::cin >> f_0 >> n;
        std::vector<long long> g(n);
        for (int j = 0; j < n; ++j){
            std::cin >> g[j];
        }

        std::vector<long long> ans = bruteForce(f_0, g);
        for (int j = 0; j < ans.size(); ++j){
            std::cout << std::to_string(ans[j]) + " ";
        }
    }
}