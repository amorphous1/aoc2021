#include <utility>
#include <vector>
#include <string>
#include <set>

using namespace std;

set<pair<int, int>> fold1(const set<pair<int, int>>& points, const pair<int, int>& fold) {
    set<pair<int, int>> folded;
    const auto& [fx, fy] = fold;
    for (const auto& [x, y] : points) {
        if (fx > 0 && x > fx) {
            folded.insert(make_pair(fx - (x - fx), y));
        } else if (fy > 0 && y > fy) {
            folded.insert(make_pair(x, fy - (y - fy)));
        } else {
            folded.insert(make_pair(x, y));
        }
    }
    return folded;
}

set<pair<int, int>> fold(set<pair<int, int>> points, const vector<pair<int, int>>& folds) {
    set<pair<int, int>> folded = move(points);
    for (pair<int, int> fold : folds) {
        folded = fold1(folded, fold);
    }
    return folded;
}

unsigned long day13a(const vector<string>& lines) {
    set<pair<int, int>> points;
    int row;
    for (row = 0; !lines.at(row).empty(); row++) {
        vector<string> x_y = split(lines.at(row), ",");
        points.insert(make_pair(stoi(x_y.at(0)), stoi(x_y.at(1))));
    }
    vector<pair<int, int>> folds;
    for (row = row + 1; row < lines.size(); row++) {
        vector<string> axis_val = split(lines.at(row), "=");
        int val = stoi(axis_val.at(1));
        folds.push_back(axis_val.at(0).ends_with('x') ? make_pair(val, 0) : make_pair(0, val));
    }
    return fold1(points, folds.at(0)).size();
}

void day13b(const vector<string>& lines) {
    set<pair<int, int>> points;
    int row;
    for (row = 0; !lines.at(row).empty(); row++) {
        vector<string> x_y = split(lines.at(row), ",");
        points.insert(make_pair(stoi(x_y.at(0)), stoi(x_y.at(1))));
    }
    vector<pair<int, int>> folds;
    for (row = row + 1; row < lines.size(); row++) {
        vector<string> axis_val = split(lines.at(row), "=");
        int val = stoi(axis_val.at(1));
        folds.push_back(axis_val.at(0).ends_with('x') ? make_pair(val, 0) : make_pair(0, val));
    }
    set<pair<int, int>> folded = fold(points, folds);
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 80; x++) {
            cout << (folded.contains(make_pair(x, y)) ? '#' : ' ');
        }
        cout << endl;
    }
}