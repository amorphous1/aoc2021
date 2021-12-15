#include <iostream>
#include <vector>
#include <fstream>
#include "common.h"
#include "day15.cpp"

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
    cout << day15a(read_lines("inputs/day15.input")) << endl;
/*
 * That's not the right answer; your answer is too high. Curiously, it's the right answer for someone else; you might be logged in to the wrong account or just unlucky. In any case, you need to be using your puzzle input. If you're stuck, make sure you're using the full input data; there are also some general tips on the about page, or you can ask for hints on the subreddit. Please wait one minute before trying again.
 */
    cout << day15b(read_lines("inputs/day15.input")) << endl;
    return 0;
}
