#include <iostream>
#include <vector>
#include <fstream>
#include "common.h"
#include "day20.cpp"

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

int main() {
    cout << day20a(read_lines("inputs/day20.input")) << endl;
    return 0;
}
