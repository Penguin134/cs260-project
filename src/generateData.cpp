//
// Created by Penguin on 12/5/23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <cstdio>

std::string generateData(int n, int range) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(-range, range); // Define the range

    std::stringstream ss;
    ss << distr(gen) << " " << std::to_string(n) << std::endl;

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
    // # of test points in a stage, sum = 240
    // i.e. stages[i] = 100, indicating that there are 100 testcases in i th stage
    std::vector<int> stages = {100, 100, 20, 10, 5, 3, 1, 1};
    //
    std::vector<int> n = {5, 20, 100, 1000, 5000, 10000, 50000, 100000};
    std::vector<int> r(300);

    int idx = 0;
    for (int stage = 0; stage < stages.size(); ++stage){
        for (int i = 0; i < stages[stage]; ++i, ++idx){
            std::ofstream outFile("./test-data/" + std::to_string(idx) + ".in");
            std::string data = generateData(n[stage], ceil(1000.0 / n[stage]));
            outFile << data << std::endl;
            outFile.close();
        }
    }

}