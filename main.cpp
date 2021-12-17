#include <iostream>
#include <vector>
#include <fstream>
#include "common.h"
#include "day16.cpp"

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
    cout << day16a(read_lines("inputs/day16.input").at(0)) << endl;
    return 0;
}
