#include <iostream>
#include <vector>
#include <fstream>
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

int main() {
    cout << day06a(read_lines("inputs/day06.input").at(0)) << endl;
    cout << day06b(read_lines("inputs/day06.input").at(0)) << endl;
    return 0;
}
