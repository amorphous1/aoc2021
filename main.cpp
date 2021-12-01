#include <iostream>
#include <vector>
#include <fstream>
#include "day01.cpp"

using namespace std;

vector<string> split(const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

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
    vector<string> lines = read_lines("inputs/day01.input");
    vector<int> depths;
    depths.resize(lines.size() ); // unfortunately this is necessary
    transform(lines.begin(), lines.end(), depths.begin(), [](const string& s) { return stoi(s); });

    cout << day01a(depths) << endl;
    cout << day01b(depths) << endl;
    return 0;
}
