#include <iostream>
#include <vector>

using namespace std;

int day01a(const vector<string>& depths) {
    int prev_depth = INT32_MAX, depth_increases = 0;
    for (const string& depth_text : depths) {
        int depth = stoi(depth_text);
        if (depth > prev_depth) {
            depth_increases++;
        }
        prev_depth = depth;
    }
    return depth_increases;
}

int day01b(const vector<string>& lines) {
    vector<int> depths;
    depths.resize(lines.size() ); // unfortunately this is necessary
    transform(lines.begin(), lines.end(), depths.begin(), [](const string& s) { return stoi(s); });

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
