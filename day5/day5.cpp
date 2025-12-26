#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

std::vector<std::pair<long, long>> mergeRanges(std::vector<std::pair<long, long>> ranges) {
    // help from: https://www.geeksforgeeks.org/dsa/merging-intervals/
    std::sort(ranges.begin(), ranges.end());
    std::vector<std::pair<long, long>> mergedRanges = {ranges[0]};

    int n = ranges.size();
    for (size_t i = 1; i < n; i++) {
        std::pair<long, long> curr = ranges[i];
        long currStart = curr.first;
        long currEnd = curr.second;
        std::pair<long, long>& last = mergedRanges.back();
        long lastEnd = last.second;

        if (currStart <= lastEnd) {
            last.second = std::max(lastEnd, currEnd);
        } else {
            mergedRanges.push_back(curr);
        }

    }

    return mergedRanges;
}

int main() {
    bool part1 = false;
    std::ifstream input("input.txt");
    std::string line;

    bool is_range = true;
    std::vector<std::pair<long, long>> ranges = {};
    long num_fresh = 0;

    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line == "") {
            is_range = false;
        }

        else if (is_range) {
            int i = line.find("-");
            long l = std::stol(line.substr(0, i));
            long r = std::stol(line.substr(i + 1));

            ranges.push_back(std::pair<long, long> (l, r));
        } else {
            if (part1) {
                long num = std::stol(line);
    
                for (const auto& [l, r] : ranges) {
                    if (l <= num && num <= r) {
                        num_fresh++;
                        break;
                    }
                }
            }
        }
    }

    if (!part1) {
        std::vector<std::pair<long, long>> mergedRanges = mergeRanges(ranges);

        for (auto [l, r] : mergedRanges)
            num_fresh += (r - l + 1);
    }

    std::cout << num_fresh << std::endl;

    input.close();
    std::cout << std::flush;
    return 0;
}