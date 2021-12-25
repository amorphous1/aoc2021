#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

pair<int, int> west_of(pair<int, int> space, int cols) {
    return space.first > 0 ? make_pair(space.first - 1, space.second) : make_pair(cols -1, space.second);
}

pair<int, int> north_of(pair<int, int> space, int rows) {
    return space.second > 0 ? make_pair(space.first, space.second  - 1) : make_pair(space.first, rows - 1);
}

unsigned long day25a(vector<string> lines) {
    set<pair<int, int>> east_moving_herd, south_moving_herd, empty_spaces;
    int rows = lines.size(), cols = lines.at(0).size();
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            pair<int, int> coord = make_pair(col, row);
            if (lines.at(row).at(col) == '>') {
                east_moving_herd.insert(coord);
            } else if (lines.at(row).at(col) == 'v') {
                south_moving_herd.insert(coord);
            } else {
                empty_spaces.insert(coord);
            }
        }
    }
    for (unsigned long step = 1;; step++) {
        map<pair<int, int>, pair<int, int>> moves_east = {}, moves_south = {};
        for (const auto& empty_space : empty_spaces) {
            pair<int, int> west_space = west_of(empty_space, cols), north_space = north_of(empty_space, rows);
            if (east_moving_herd.contains(west_space)) {
                moves_east[west_space] = empty_space;
                if (south_moving_herd.contains(north_of(west_space, rows))) {
                    moves_south[north_of(west_space, rows)] = west_space;
                }
            } else if (south_moving_herd.contains(north_space)) {
                moves_south[north_space] = empty_space;
            }
        }
        if (moves_east.empty() && moves_south.empty()) {
            return step;
        }
        for (const auto& [from_west, to_east] : moves_east) {
            east_moving_herd.erase(from_west); east_moving_herd.insert(to_east);
            empty_spaces.insert(from_west);    empty_spaces.erase(to_east);
        }
        for (const auto& [from_north, to_south] : moves_south) {
            south_moving_herd.erase(from_north); south_moving_herd.insert(to_south);
            empty_spaces.insert(from_north);     empty_spaces.erase(to_south);
        }
    }
}
