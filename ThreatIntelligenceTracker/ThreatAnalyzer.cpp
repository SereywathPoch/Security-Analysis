// File: ThreatAnalyzer.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sstream>

int main() {
    std::ifstream log_file("collected_network.log");
    std::ifstream threat_file("threat_feed.csv");
    std::ofstream report_file("threat_report.csv");

    if (!log_file.is_open() || !threat_file.is_open() || !report_file.is_open()) {
        std::cerr << "Error opening files\n";
        return 1;
    }

    // Load threat feed IPs into a set
    std::set<std::string> threat_ips;
    std::string line;
    while (getline(threat_file, line)) {
        std::stringstream ss(line);
        std::string ip;
        getline(ss, ip, ',');  // Assuming CSV: ip,description
        threat_ips.insert(ip);
    }

    // Analyze network logs
    report_file << "Malicious_IP,Log_Line\n";
    while (getline(log_file, line)) {
        std::stringstream ss(line);
        std::string ip;
        ss >> ip;  // assume IP is first word
        if (threat_ips.find(ip) != threat_ips.end()) {
            report_file << ip << "," << line << "\n";
        }
    }

    std::cout << "Threat report generated: threat_report.csv\n";
    return 0;
}