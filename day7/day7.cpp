#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <ranges>
#include <cmath>
#include <cstdint>
#include <unordered_map>

typedef uint8_t u8;
typedef uint64_t u64;
using Key = std::tuple<u64, u64, std::string>;

struct KeyHash {
    std::size_t operator()(const Key& k) const {
        auto [r, c, row] = k;

        return ((std::hash<u64>()(r)
             ^ (std::hash<u64>()(c) << 1)) >> 1)
             ^ (std::hash<std::string>()(row) << 1);
    }
};

u64 get_classical_num_splits(std::vector<std::string> G) {
    u64 num_splits = 0;
    
    for (auto const& [r, row] : std::views::enumerate(G)) {
        if (r == 0) {
            continue;
        }
        
        for (auto const& [c, ch] : std::views::enumerate(row)) {
            if (ch == '^') {
                if (G[r - 1][c] == '|') {
                    num_splits++;
                    G[r][c -  1] = '|';
                    G[r][c +  1] = '|';
                }
            } else if (ch == '.') {
                if (G[r - 1][c] == 'S' || G[r - 1][c] == '|') {
                    G[r][c] = '|';
                }
            }
        }

    }

    for (auto& row: G) {
        std::cout << row << std::endl;
    }

    return num_splits;
}

u64 dfs(std::vector<std::string>& G, u64 r, u64 c, bool is_split, std::unordered_map<Key, u64, KeyHash>& cache) {
    if (r == G.size()) {
        return 1;
    }

    std::string row = G[r];
    Key key = {r, c, row};

    if (!is_split) {
        if (cache.count(key)) {
            return cache[key];
        }
    }

    u64 num_splits = 0;

    for (auto const& [c, ch] : std::views::enumerate(row)) {
        if (ch == '^') {
            if (G[r - 1][c] == '|') {
                G[r][c -  1] = '|';

                num_splits += dfs(G, r + 1, c, true, cache);

                u64 tr = r;
                while (tr < G.size() && G[tr][c - 1] == '|') {
                    G[tr][c - 1] = '.';
                    tr++;
                }

                G[r][c +  1] = '|';

                num_splits += dfs(G, r + 1, c, true, cache);

                tr = r;
                while (tr < G.size() && G[tr][c + 1] == '|') {
                    G[tr][c + 1] = '.';
                    tr++;
                }
            }
        } else if (ch == '.') {
            if (G[r - 1][c] == 'S' || G[r - 1][c] == '|') {
                G[r][c] = '|';
                num_splits += dfs(G, r + 1, c, false, cache);
            }
        }
    }

    cache[key] = num_splits;

    for (const auto& [key, value] : cache) {
        auto [r, c, row] = key;
    }

    return num_splits;
}

u64 get_quantum_num_splits(std::vector<std::string> G) {
    std::unordered_map<Key, u64, KeyHash> cache;
    return dfs(G, 1, 0, false, cache);
}

int main() {
    bool part1 = false;
    std::ifstream input("input.txt");
    std::string line;

    std::vector<std::string> G;
    
    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        G.push_back(line);
    }

    u64 num_splits;
    if (part1) {
        num_splits = get_classical_num_splits(G);
    } else {
        num_splits = get_quantum_num_splits(G);
    }

    std::cout << num_splits << std::endl;

    input.close();
    return 0;
}