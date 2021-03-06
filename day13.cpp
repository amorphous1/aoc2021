#include <vector>
#include <string>
#include <set>

using namespace std;

set<pair<int, int>> fold(const set<pair<int, int>>& points, const pair<int, int>& fold) {
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

pair<set<pair<int, int>>, vector<pair<int, int>>> parse_points_and_folds(const vector<string> &lines) {
    set<pair<int, int>> points;
    vector<pair<int, int>> folds;
    int row;
    for (row = 0; !lines.at(row).empty(); row++) {
        const auto& [x, y] = split_pair(lines.at(row), ",");
        points.insert(make_pair(stoi(x), stoi(y)));
    }
    for (row = row + 1; row < lines.size(); row++) {
        const auto& [axis, val] = split_pair(lines.at(row), "=");
        folds.push_back(axis.ends_with('x') ? make_pair(stoi(val), 0) : make_pair(0, stoi(val)));
    }
    return make_pair(points, folds);
}

unsigned long day13a(const vector<string>& lines) {
    const auto& [points, folds] = parse_points_and_folds(lines);
    return fold(points, folds.at(0)).size();
}

void day13b(const vector<string>& lines) {
    auto [points, folds] = parse_points_and_folds(lines);
    for (pair<int, int> fold_line : folds) {
        points = fold(points, fold_line);
    }
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 80; x++) {
            cout << (points.contains(make_pair(x, y)) ? '#' : ' ');
        }
        cout << endl;
    }
}