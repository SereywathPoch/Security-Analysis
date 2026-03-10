// File: Log-Processor.cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream infile("system.log");
    std::ofstream outfile("filtered_logs.csv");
    std::string line;
    while (getline(infile, line)) {
        if (line.find("failed") != std::string::npos || line.find("unauthorized") != std::string::npos) {
            outfile << line << std::endl;
        }
    }
    std::cout << "Filtered logs saved to filtered_logs.csv\n";
    return 0;
}