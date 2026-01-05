#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

enum class Op {
    ADD,
    MUL,
};

std::vector<std::vector<long>> get_all_nums(std::vector<std::string> lines) {
    std::vector<std::vector<long>> all_nums;
    
    for (size_t i = 0; i < lines.size() - 1; i++) {
        std::stringstream ss(lines[i]);
        std::vector<long> nums;
        long num;
        
        while (ss >> num) {
            nums.push_back(num);
        }
        
        all_nums.push_back(nums);
    }

    return all_nums;
}

std::vector<std::string> get_chars(std::string last) {
    std::vector<std::string> chars;
    std::stringstream ss(last);
    std::string ch;

    while (ss >> ch) {
        chars.push_back(ch);
    }

    return chars;
}

long get_grand_total(std::vector<std::vector<long>> all_nums, std::vector<std::string> chars) {
    size_t n = all_nums[0].size();
    size_t m = all_nums.size();
    long grand_total = 0;

    for (size_t i = 0; i < n; i++) {
        Op curr_op = (chars[i] == "+") ? Op::ADD : Op::MUL;
        long total = (curr_op == Op::ADD) ? 0 : 1;
        for (size_t j = 0; j < m; j++) {
            long num = all_nums[j][i];
            if (curr_op == Op::ADD) {
                total += num;
            } else if (curr_op == Op::MUL) {
                total *= num;
            }
        }
        grand_total += total;
    }

    return grand_total;
}

long get_grand_total_p2(std::vector<std::string> lines) {
    long grand_total = 0;

    Op curr_op = Op::ADD;
    long problem_total = 0;
    int m = lines[0].length();

    for (int j = 0; j < m; j++) {
        bool is_empty_col = true;
        long col_num = 0;

        for (auto& row: lines) {
            char ch = row[j];
            if (ch == ' ') {
                continue;;
            } else if (ch == '+') {
                curr_op = Op::ADD;
                problem_total = 0;
                continue;
            } else if (ch == '*') {
                curr_op = Op::MUL;
                problem_total = 1;
                continue;
            } else {
                is_empty_col = false;
                long num = ch - '0';
                col_num = 10 * col_num + num;
            }
        }

        if (is_empty_col) {
            grand_total += problem_total;
            continue;
        }

        if (curr_op == Op::ADD) {
            problem_total += col_num;
        } else if (curr_op == Op::MUL) {
            problem_total *= col_num;
        }

    }

    return grand_total;
}

int main() {
    bool part1 = false;
    std::ifstream input("input.txt");
    std::string line;

    std::vector<std::string> lines;
    
    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        lines.push_back(line);
    }
    
    long grand_total = 0;
    if (part1) {
        std::vector<std::vector<long>> all_nums = get_all_nums(lines);
        std::string last = lines.back();
        std::vector<std::string> chars = get_chars(last);
        
        grand_total = get_grand_total(all_nums, chars);
    } else {
        grand_total = get_grand_total_p2(lines);
    }

    std::cout << grand_total << std::endl;

    input.close();
    return 0;
}