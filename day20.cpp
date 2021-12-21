#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

char enhance(const pair<int, int>& coord, const map<pair<int, int>, char> &pixels,
             const string &enhancement_algo, int step, set<pair<int, int>>& new_neighbours) {
    string enhancement;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            const auto& neighbour = make_pair(coord.first + dx, coord.second + dy);
            if (pixels.contains(neighbour)) {
                enhancement += pixels.at(neighbour);
            } else {
                enhancement += enhancement_algo.at(0) == '.' ? '0' : (step % 2 == 1 ? '0' : '1');
                new_neighbours.insert(neighbour);
            }
        }
    }
    return enhancement_algo.at(stoi(enhancement, nullptr, 2)) == '#' ? '1' : '0';
}

void print_pixels(map<pair<int, int>, char> pixels, int step) {
    cout << endl << "---------- after step " << step << ":" << endl;
    int min_x = 123, max_x = 0, min_y = 123, max_y = 0;
    for (const auto& [coord, color] : pixels) {
        min_x = min(coord.first, min_x);
        max_x = max(coord.first, max_x);
        min_y = min(coord.second, min_y);
        max_y = max(coord.second, max_y);
    }
    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            cout << (pixels[make_pair(x, y)] == '1' ? '#' : '.');
        }
        cout << endl;
    }
}

unsigned long day20a(const vector<string>& lines) {
    string enhancement_algo = lines.at(0);
    map<pair<int, int>, char> pixels;
    for (int y = 2; y < lines.size(); y++) {
        for (int x = 0; x < lines.at(y).size(); x++) {
            pixels[make_pair(x, y)] = lines.at(y).at(x) == '#' ? '1' : '0';
        }
    }
    for (int step = 1; step <= 2; step++) {
        map<pair<int, int>, char> updated_pixels = {};
        set<pair<int, int>> new_neighbours = {};
        for (const auto& [coord, _] : pixels) {
            updated_pixels[coord] = enhance(coord, pixels, enhancement_algo, step, new_neighbours);
        }
        set<pair<int, int>> ignored_neighbours;
        for (const auto& new_neighbour : new_neighbours) {
            updated_pixels[new_neighbour] = enhance(new_neighbour, pixels, enhancement_algo, step, ignored_neighbours);
        }
        pixels = updated_pixels;
        print_pixels(pixels, step);
    }
    unsigned long lit_pixels = 0;
    for (const auto& [_, color] : pixels) {
        lit_pixels += (color - '0');
    }
    return lit_pixels;
}
