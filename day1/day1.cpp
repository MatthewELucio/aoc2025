#include <iostream>
#include <fstream>
#include <string>

int p1turn(int dial, bool isLeft, int distance) {
    int M = 100;
    if (isLeft) {
        int res = (dial - distance) % M;
        return (res < 0) ? (res + M) : res;
    } else {
        return (dial + distance) % M;
    }
}

int p2turn(int dial, bool isLeft, int distance, int& numClicks) {
    int M = 100;
    numClicks = 0;
    if (isLeft) {
        int res = (dial - distance) % M;
        numClicks = -(dial - distance) / M;
        if (dial != 0 && res < 0) numClicks += 1;
        return (res < 0) ? (res + M) : res;
    } else {
        numClicks = (dial + distance) / M;
        if ((dial + distance) % M == 0) numClicks -= 1; 
        return (dial + distance) % M;
    }
}

int main() {
    bool part1 = false;

    int dial = 50;
    int numDialZero = 0;
    int numClicks = 0;

    std::ifstream input("input.txt");
    std::string line;

    while (std::getline(input, line)) {
        char dir = line[0];
        int distance = std::stoi(line.substr(1, 3));

        if (part1) {
            dial = p1turn(dial, dir == 'L', distance);
            numDialZero += dial == 0;
        } else {
            dial = p2turn(dial, dir == 'L', distance, numClicks);
            numDialZero += dial == 0;
            numDialZero += numClicks;
        }
    }
    input.close();

    std::cout << numDialZero << "\n";

    return 0;
}