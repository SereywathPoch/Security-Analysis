// File: Analyze.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Example suspicious domains
std::vector<std::string> suspicious_domains = {"bit.ly", "tinyurl.com", "malicious.com"};

bool contains_suspicious(const std::string &line) {
    for (auto &domain : suspicious_domains) {
        if (line.find(domain) != std::string::npos)
            return true;
    }
    return false;
}

int main() {
    std::string email_folder = "C:\\Users\\Apple\\Downloads\\Sereywath\\emails";
    std::ofstream report("phishing_report.csv");
    report << "File,Suspicious_Links\n";

    for (const auto &entry : fs::directory_iterator(email_folder)) {
        if (entry.path().extension() == ".eml") {
            std::ifstream email_file(entry.path());
            std::string line;
            std::vector<std::string> suspicious_lines;
            while (std::getline(email_file, line)) {
                if (contains_suspicious(line)) {
                    suspicious_lines.push_back(line);
                }
            }
            // Write to CSV
            report << entry.path().filename().string() << ",";
            for (size_t i = 0; i < suspicious_lines.size(); ++i) {
                report << suspicious_lines[i];
                if (i != suspicious_lines.size() - 1) report << "; ";
            }
            report << "\n";
        }
    }

    std::cout << "Phishing analysis complete. Report saved to phishing_report.csv\n";
    return 0;
}