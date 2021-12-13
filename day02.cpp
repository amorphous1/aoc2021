#include <iostream>
#include <vector>
#include "common.h"

using namespace std;

int day02a(const vector<string>& commands) {
    int x = 0, y = 0;
    for (const string& cmd : commands) {
        const auto& [direction, distance_text] = split_pair(cmd, " ");
        int distance = stoi(distance_text);
        if (direction == "forward") x += distance;
        else if (direction == "up") y -= distance;
        else if (direction == "down") y += distance;
        else throw invalid_argument("unknown direction: " + direction);
    }
    return x * y;
}

int day02b(const vector<string>& commands) {
    int x = 0, y = 0, aim = 0;
    for (const string& cmd : commands) {
        const auto& [direction, value_text] = split_pair(cmd, " ");
        int val = stoi(value_text);
        if (direction == "forward") {
            x += val;
            y += aim * val;
        }
        else if (direction == "up") aim -= val;
        else if (direction == "down") aim += val;
        else throw invalid_argument("unknown direction: " + direction);
    }
    return x * y;
}
