#include <vector>
#include <string>
#include <set>
#include "common.h"

using namespace std;

vector<vector<int>> parse(const vector<string>& lines) {
    vector<vector<int>> grid;
    grid.reserve(lines.size());
    for (const string& line : lines) {
        grid.push_back(ints(split(line, "")));
    }
    return grid;
}

int day09a(const vector<string>& lines) {
    vector<vector<int>> grid = parse(lines);
    int rows = (int)grid.size(), cols = (int)grid[0].size(), result = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if ( (r == 0        || grid[r-1][c] > grid[r][c]) &&
                 (r == rows - 1 || grid[r+1][c] > grid[r][c]) &&
                 (c == 0        || grid[r][c-1] > grid[r][c]) &&
                 (c == cols - 1 || grid[r][c+1] > grid[r][c])) {
                result += 1 + grid[r][c];
            }
        }
    }
    return result;
}

int find_basin_size(const pair<int, int>& start, const vector<vector<int>>& grid, set<pair<int, int>>& unexplored) {
    set<pair<int, int>> basin = { }, edge = { start };
    unexplored.erase(start);
    do {
        pair<int, int> current = *edge.begin();
        basin.insert(current);
        edge.erase(current);
        const vector<pair<int, int>> candidates = {
                make_pair(current.first - 1, current.second), make_pair(current.first + 1, current.second),
                make_pair(current.first, current.second - 1), make_pair(current.first, current.second + 1),
        };
        for (const pair<int, int>& candidate : candidates) {
            if (unexplored.contains(candidate) && grid[candidate.first][candidate.second] < 9) {
                edge.insert(candidate);
            }
            unexplored.erase(candidate);
        }
    } while (!edge.empty());
    return (int)basin.size();
}

int day09b(const vector<string>& lines) {
    vector<vector<int>> grid = parse(lines);
    int rows = (int)grid.size(), cols = (int)grid[0].size();
    set<pair<int, int>> unexplored;
    vector<int> basin_sizes;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            unexplored.insert(make_pair(r, c));
        }
    }
    while (!unexplored.empty()) {
        pair<int, int> point = *unexplored.begin();
        if (grid[point.first][point.second] == 9) {
            unexplored.erase(point);
        } else {
            basin_sizes.push_back(find_basin_size(point, grid, unexplored));
        }
    }
    sort(basin_sizes.rbegin(), basin_sizes.rend());
    return basin_sizes[0] * basin_sizes[1] * basin_sizes[2];
}
