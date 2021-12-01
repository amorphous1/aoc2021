#include <iostream>
#include <vector>

using namespace std;

int day01a(vector<int> &depths) {
    int prev_depth = INT32_MAX, depth_increases = 0;
    for (int depth : depths) {
        if (depth > prev_depth) {
            depth_increases++;
        }
        prev_depth = depth;
    }
    return depth_increases;
}

int day01b(vector<int> &depths) {
    int prev_window = INT32_MAX, depth_increases = 0;
    for (int i = 0; i < depths.size() - 2; i++) {
        int current_window = depths.at(i) + depths.at(i+1) + depths.at(i+2);
        if (current_window > prev_window) {
            depth_increases++;
        }
        prev_window = current_window;
    }
    return depth_increases;
}
