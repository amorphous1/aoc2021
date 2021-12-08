#include <iostream>
#include <vector>
#include <fstream>
#include "common.h"
#include "day08.cpp"

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
    cout << day08a(read_lines("inputs/day08.input")) << endl;
    cout << day08b(read_lines("inputs/day08.input")) << endl;
    return 0;
}
