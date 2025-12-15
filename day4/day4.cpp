#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int get_neighbors(std::vector<std::string> G, int r, int c, int R, int C) {
    int neighbors = 0;

    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) {
                continue;
            }

            int nr = r + dr;
            int nc = c + dc;

            if (0 <= nr && nr < R && 0 <= nc && nc < C && G[nr][nc] == '@') {
                neighbors++;
            }
        }
    }

    return neighbors;
}

int get_rolls(std::vector<std::string> &G) {
    int R = G.size();
    int C = G[0].length();
    int rolls = 0;
    std::vector<std::pair<int, int>> accessed_coords = {};
    std::vector<std::pair<int, int>> old_x_coords = {};

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (G[r][c] == '.') {
                continue;
            }
            if (G[r][c] == 'x') {
                old_x_coords.push_back(std::pair<int, int>(r, c));
                continue;
            }

            int neighbors = get_neighbors(G, r, c, R, C);
            if (neighbors < 4) {
                rolls++;
                accessed_coords.push_back(std::pair<int, int>(r, c));
            }
        }
    }

    for (auto& pair: accessed_coords) {
        int r = pair.first;
        int c = pair.second;

        G[r][c] = 'x';
    }

    for (auto& pair: old_x_coords) {
        int r = pair.first;
        int c = pair.second;

        G[r][c] = '.';
    }

    return rolls;
}

int main() {
    bool part1 = true;

    std::ifstream input("input.txt");
    std::string line;

    std::vector<std::string> G;

    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        G.push_back(line);
    }

    if (part1) {
        int rolls = get_rolls(G);
        std::cout << rolls << std::endl;
    } else {
        int total_rolls = 0;
        int rolls;
        for (auto row : G ) {
            std::cout << row << std::endl;
        }
        std::cout << std::endl;

        while ((rolls = get_rolls(G)) > 0) {
            for (auto row : G ) {
                std::cout << row << std::endl;
            }

            total_rolls += rolls;
        }
        std::cout << total_rolls << std::endl;
    }

    input.close();
    std::cout << std::flush;
    return 0;
}