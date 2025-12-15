#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int getMaxDigInRange(std::string line, int &j, int k, int n) {
    char max = '0';
    for (int i = j; i < n - k; i++) {
        auto ch = line[i];

        if (ch > max) {
            max = ch;
            j = i + 1;
        }
    }
    return max - '0';
}

long getMaxJoltage(std::string line, int num_batteries) {
    int j = 0;
    int n = line.length();
    long maxjoltage = 0;
    
    for (int k = num_batteries - 1; k >= 0; k--) {
        int dig = getMaxDigInRange(line, j, k, n);
        maxjoltage = 10 * maxjoltage + dig;
    }

    return maxjoltage;
}

int main() {
    bool part1 = false;

    std::ifstream input("input.txt");
    std::string line;
    long totalJoltage = 0;

    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        long maxjoltage = 0;
        if (part1) {
            maxjoltage = getMaxJoltage(line, 2);
        } else {
            maxjoltage = getMaxJoltage(line, 12);
        }
        totalJoltage += maxjoltage;
    }

    std::cout << totalJoltage << "\n";

    input.close();
    std::cout << std::flush;
    return 0;
}