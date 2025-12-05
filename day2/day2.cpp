#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

bool repeatsMTimes(std::string s, int m, int n) {
    if (n % m != 0) {
        return false;
    } 
    
    int d = n / m;
    std::string start = s.substr(0, d);

    for (int i = d; i < n; i += d) {
        std::string curr = s.substr(i, d);
        if (start != curr) {
            return false;
        }
    }
    
    return true;
}

int main() {
    bool part1 = false;

    std::ifstream input("input.txt");
    std::string line;

    std::getline(input, line);
    std::stringstream ss(line);
    std::string range;

    long invalidIdSum = 0;

    while (std::getline(ss, range, ',')) {
        int i = range.find("-");
        long l = std::stol(range.substr(0, i));
        long r = std::stol(range.substr(i + 1));

        for (long num = l; num < r + 1; num++) {
            std::string s = std::to_string(num);
            int n = s.length();

            if (part1) {
                std::string lhs = s.substr(0, n/2);
                std::string rhs = s.substr(n/2);
    
                if (lhs == rhs) {
                    invalidIdSum += num;
                }
            } else {
                for (int m = 2; m <= n; m++) {
                    if (repeatsMTimes(s, m, n)) {
                        invalidIdSum += num;
                        // std::cout << range << " " << invalidIdSum << " " << num << " " << m << " " << n << "\n";
                        break;
                    }
                }
            }
        }
    }

    
    input.close();
    std::cout << invalidIdSum << "\n";

    return 0;
}