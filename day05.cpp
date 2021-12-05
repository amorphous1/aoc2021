#include <utility>
#include <vector>
#include <map>
#include "common.h"

#define SIZE 5
using namespace std;

pair<int, int> parse_coord(const string& coord_text) {
    vector<string> x_y = split(coord_text, ",");
    return make_pair(stoi(x_y.at(0)), stoi(x_y.at(1)));
}

int day05a(const vector<string>& lines) {
    map<pair<int, int>, int> coord_to_lines = {};
    for (const string& line : lines) {
        const auto coord1_coord2 = split(line, " -> ");
        const auto coord1 = parse_coord(coord1_coord2.at(0));
        const auto coord2 = parse_coord(coord1_coord2.at(1));
        if (coord1.first == coord2.first || coord1.second == coord2.second) {
            for (int x = min(coord1.first, coord2.first); x <= max(coord1.first, coord2.first); x++) {
                for (int y = min(coord1.second, coord2.second); y <= max(coord1.second, coord2.second); y++) {
                    const auto coord = make_pair(x, y);
                    coord_to_lines[coord] = coord_to_lines[coord] + 1;
                }
            }
        }
    }
    int two_or_more_overlapping_lines = 0;
    for (const auto& [coord, num_lines] : coord_to_lines) {
        if (num_lines > 1) {
            two_or_more_overlapping_lines++;
        }
    }
    return two_or_more_overlapping_lines;
}

int day05b(const vector<string>& lines) {
    map<pair<int, int>, int> coord_to_lines = {};
    for (const string& line : lines) {
        const auto coord1_coord2 = split(line, " -> ");
        const auto coord1 = parse_coord(coord1_coord2.at(0));
        const auto coord2 = parse_coord(coord1_coord2.at(1));
        const auto delta_x = coord2.first - coord1.first, delta_y = coord2.second - coord1.second;
        for (int step = 0; step <= max(abs(delta_x), abs(delta_y)); step++) {
            const auto coord = make_pair(coord1.first + step*sgn(delta_x), coord1.second + step*sgn(delta_y));
            coord_to_lines[coord] = coord_to_lines[coord] + 1;
        }
    }
    int coords_with_overlapping_lines = 0;
    for (const auto& [coord, num_lines] : coord_to_lines) {
        if (num_lines > 1) {
            coords_with_overlapping_lines++;
        }
    }
    return coords_with_overlapping_lines;
}
