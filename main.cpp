#include <iostream>
#include <vector>
#include <fstream>
#include "common.h"
#include "day06.cpp"

using namespace std;

vector<string> read_lines(const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "cannot open file " << file_name << endl;
        exit(1);
    }
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

vector<int> ints(const vector<string>& numbers) {
    vector<int> result;
    result.resize(numbers.size() ); // unfortunately this is necessary
    transform(numbers.begin(), numbers.end(), result.begin(), [](const string& s) { return stoi(s); });
    return result;
}

int main() {
    vector<int> positions = ints(split(read_lines("inputs/day07.input").at(0), ","));
    cout << day06a(timer_vals) << endl;
    cout << day06b(timer_vals) << endl;
    return 0;
}
