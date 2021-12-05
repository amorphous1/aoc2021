#include <iostream>
#include <vector>
#include "common.h"

using namespace std;

int day02a(const vector<string>& commands) {
    int x = 0, y = 0;
    for (const string& cmd : commands) {
        auto split_cmd = split(cmd, " ");
        string direction = split_cmd.at(0);
        int distance = stoi(split_cmd.at(1));
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
        auto split_cmd = split(cmd, " ");
        string direction = split_cmd.at(0);
        int val = stoi(split_cmd.at(1));
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
