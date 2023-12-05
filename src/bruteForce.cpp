#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <cstdio>

std::vector<double> bruteForce(double f_0, std::vector<double>& g){
    std::vector<double> f(g.size(),0);
    f[0] = f_0;
    for (int i = 1; i < f.size(); ++i){
        double tmp = 0;
        for (int j = 1; j <= i; ++j){
            tmp += f[i - j] * g[j];
        }
        f[i] = tmp;
    }
    return f;
}

std::string generateData(int n, double range) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(-range, range); // Define the range

    std::stringstream ss;
    ss << distr(gen) << std::endl;

    for (int i = 0; i < n; ++i) {
        double number = distr(gen); // Generate a random number
        ss << number;
        if (i < n - 1) {
            ss << " "; // Add a space after each number except the last
        }
    }
    return ss.str();
}

int main(){
    int n[] = {5, 10, 100, 500, 1000};
    double r[] = {50, 10, 1.01, 0.5, 0.2};
    // generate test cases
//    for (int i = 0; i < 5; ++i){
//        std::ofstream outFile("./test-data/" + std::to_string(i) + ".in");
//        std::string data = generateData(n[i], r[i]);
//        outFile << data << std::endl;
//        outFile.close();
//    }

    for (int i = 0; i < 5; ++i){
        std::string inName = "./test-data/" + std::to_string(i) + ".in";
        std::string outName = "./test-data/" + std::to_string(i) + ".out";
        std::freopen(inName.c_str(),"r",stdin);
        std::freopen(outName.c_str(),"w",stdout);

        double f_0;
        std::cin >> f_0;
        std::vector<double> g(n[i]);
        for (int j = 0; j < n[i]; ++j){
            std::cin >> g[j];
        }

        std::vector<double> ans = bruteForce(f_0, g);
        for (int j = 0; j < ans.size(); ++j){
            std::cout << std::to_string(ans[j]) + " ";
        }
    }
}