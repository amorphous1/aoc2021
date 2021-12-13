#include <map>
#include "common.h"

using namespace std;

pair<int, int> parse_coord(const string& coord_text) {
    const auto& [x, y] = split_pair(coord_text, ",");
    return make_pair(stoi(x), stoi(y));
}

int overlapping_lines(const vector<string>& lines, const bool consider_diagonals) {
    map<pair<int, int>, int> coord_to_lines = {};
    for (const string& line : lines) {
        const auto& [coord1_text, coord2_text] = split_pair(line, " -> ");
        const auto& [x1, y1] = parse_coord(coord1_text);
        const auto& [x2, y2] = parse_coord(coord2_text);
        const auto delta_x = x2 - x1, delta_y = y2 - y1;
        if (consider_diagonals || delta_x == 0 || delta_y == 0) {
            for (int step = 0; step <= max(abs(delta_x), abs(delta_y)); step++) {
                const auto coord = make_pair(x1 + step * sgn(delta_x), y1 + step * sgn(delta_y));
                coord_to_lines[coord]++;
            }
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

int day05a(const vector<string>& lines) {
    return overlapping_lines(lines, false);
}

int day05b(const vector<string>& lines) {
    return overlapping_lines(lines, true);
}