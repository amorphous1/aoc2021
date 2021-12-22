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
    Point3d p_min, p_max;

    set<Cube> split_using(const Cube& other) {
        if (other.contains(*this)) {
            return {};
        } else if (disjoint_with(other)) {
            return { *this };
        }
        set<Cube> splits;
        Cube left_of_other = { p_min, { min(p_max.x, other.p_min.x - 1), p_max.y, p_max.z } };
        if (left_of_other.is_valid()) {
            splits.insert(left_of_other);
        }
        Cube right_of_other = { { max(p_min.x, other.p_max.x + 1), p_min.y, p_min.z }, p_max };
        if (right_of_other.is_valid()) {
            splits.insert(right_of_other);
        }
        Cube below_other = { // and not containing any points from left_of_other and right_of_other
                { left_of_other.is_valid() ? left_of_other.p_max.x + 1 : p_min.x, p_min.y, p_min.z },
                { right_of_other.is_valid() ? right_of_other.p_min.x - 1 : p_max.x, min(p_max.y, other.p_min.y - 1), p_max.z }
        };
        if (below_other.is_valid()) {
            splits.insert(below_other);
        }
        Cube above_other = { // and not containing any points from left_of_other and right_of_other
                { left_of_other.is_valid() ? left_of_other.p_max.x + 1 : p_min.x, max(p_min.y, other.p_max.y + 1), p_min.z },
                { right_of_other.is_valid() ? right_of_other.p_min.x - 1 : p_max.x, p_max.y, p_max.z }
        };
        if (above_other.is_valid()) {
            splits.insert(above_other);
        }
        Cube in_front_of_other = { // and not containing any points from left_of_other/right_of_other/below_other/above_other
                {
                    left_of_other.is_valid() ? left_of_other.p_max.x + 1 : p_min.x,
                    below_other.is_valid() ? below_other.p_max.y + 1 : p_min.y,
                    p_min.z
                },
                {
                    right_of_other.is_valid() ? right_of_other.p_min.x - 1 : p_max.x,
                    above_other.is_valid() ? above_other.p_min.y - 1 : p_max.y,
                    min(p_max.z, other.p_min.z - 1)
                }
        };
        if (in_front_of_other.is_valid()) {
            splits.insert(in_front_of_other);
        }
        Cube behind_other = {  // and not containing any points from left_of_other/right_of_other/below_other/above_other
                {
                        left_of_other.is_valid() ? left_of_other.p_max.x + 1 : p_min.x,
                        below_other.is_valid() ? below_other.p_max.y + 1 : p_min.y,
                        max(p_min.z, other.p_max.z + 1)
                },
                {
                        right_of_other.is_valid() ? right_of_other.p_min.x - 1 : p_max.x,
                        above_other.is_valid() ? above_other.p_min.y - 1 : p_max.y,
                        p_max.z
                }
        };
        if (behind_other.is_valid()) {
            splits.insert(behind_other);
        }
        return splits;
    }

    [[nodiscard]] bool disjoint_with(Cube other) const {
        return p_min.x > other.p_max.x || p_max.x < other.p_min.x ||
               p_min.y > other.p_max.y || p_max.y < other.p_min.y ||
               p_min.z > other.p_max.z || p_max.z < other.p_min.z;
    }
    [[nodiscard]] bool is_valid() const {
        return p_min.x <= p_max.x && p_min.y <= p_max.y && p_min.z <= p_max.z;
    }
    [[nodiscard]] bool contains(Cube other) const {
        return contains(other.p_min) && contains(other.p_max);
    }
    [[nodiscard]] bool contains(Point3d point) const {
        return point.x >= p_min.x && point.x <= p_max.x &&
               point.y >= p_min.y && point.y <= p_max.y &&
               point.z >= p_min.z && point.z <= p_max.z;
    }
    [[nodiscard]] unsigned long num_points() const {
        return (unsigned long)(p_max.x - p_min.x + 1) * (p_max.y - p_min.y + 1) * (p_max.z - p_min.z + 1);
    }
    bool operator==(const Cube& other) const {
        return p_min == other.p_min && p_max == other.p_max;
    }
    bool operator<(const Cube &other) const {
        return p_min < other.p_min || (p_min == other.p_min && p_max < other.p_max);
    }
};

vector<pair<Cube, bool>> parse_cubes(const vector<string>& lines, const int max_abs_pos) {
    vector<pair<Cube, bool>> cubes;
    for (const string& line : lines) {
        vector<int> border = find_numbers(line);
        if (max_abs_pos < 0 || all_of(border.begin(), border.end(), [max_abs_pos](int pos){ return abs(pos) <= max_abs_pos; })) {
            cubes.emplace_back(
                    Cube { { border.at(0), border.at(2), border.at(4) }, { border.at(1), border.at(3), border.at(5) } },
                    line.starts_with("on"));
        }
    }
    return cubes;
}

unsigned long count_points(vector<pair<Cube, bool>> &cubes) {
    set<Cube> disjoint_cubes = {cubes.at(0).first };
    for (int i = 1; i < cubes.size(); i++) {
        const auto& [next_cube, next_cube_is_on] = cubes.at(i);
        set<Cube> new_disjoint_cubes = {};
        for (Cube disjoint_cube : disjoint_cubes) {
            set<Cube> split_cubes = disjoint_cube.split_using(next_cube);
            new_disjoint_cubes.insert(split_cubes.begin(), split_cubes.end());
        }
        if (next_cube_is_on) {
            new_disjoint_cubes.insert(next_cube);
        }
        disjoint_cubes = new_disjoint_cubes;
    }
    unsigned long total_points = 0;
    for (Cube cube : disjoint_cubes) {
        total_points += cube.num_points();
    }
    return total_points;
}

unsigned long day22a(const vector<string>& lines) {
    vector<pair<Cube, bool>> cubes = parse_cubes(lines, 50);
    return count_points(cubes);
}

unsigned long day22b(const vector<string>& lines) {
    vector<pair<Cube, bool>> cubes = parse_cubes(lines, -1);
    return count_points(cubes);
}