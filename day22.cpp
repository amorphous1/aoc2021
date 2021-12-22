#include <set>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

struct Point3d {
    int x, y, z;
    bool operator==(const Point3d& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    bool operator<(const Point3d &other) const {
        return x < other.x || (x == other.x && y < other.y) || (x == other.x && y == other.y && z < other.z);
    }
};
struct Cube {
    bool is_on;
    Point3d p_min, p_max;

    set<Point3d> to_points() const {
        set<Point3d> points;
        for (int x = max(p_min.x, -50); x <= min(p_max.x, 50); x++) {
            for (int y = max(p_min.y, -50); y <= min(p_max.y, 50); y++) {
                for (int z = max(p_min.z, -50); z <= min(p_max.z, 50); z++) {
                    points.insert({x, y, z});
                }
            }
        }
        return points;
    }
};

unsigned long day22a(const vector<string>& lines) {
    vector<Cube> cubes;
    for (const string& line : lines) {
        vector<int> border = find_numbers(line);
        cubes.push_back({ line.starts_with("on"),
                          { border.at(0), border.at(2), border.at(4) }, { border.at(1), border.at(3), border.at(5) } });
    }
    set<Point3d> on_points;
    for (const Cube& cube : cubes) {
        set<Point3d> cube_points = cube.to_points(), new_on_points;
        if (cube.is_on) {
            set_union(on_points.begin(), on_points.end(), cube_points.begin(), cube_points.end(), inserter(new_on_points, new_on_points.begin()));
        } else {
            set_difference(on_points.begin(), on_points.end(), cube_points.begin(), cube_points.end(), inserter(new_on_points, new_on_points.begin()));
        }
        on_points = new_on_points;
    }
    return on_points.size();
}
