#include <vector>
#include <string>
#include <set>

using namespace std;

unsigned long day17a(const string& input) {
    int y_min = find_numbers(input).at(2);
    // if you launch a missile with vertical speed sy, it will come back to the x-axis (y=0) with speed -sy, then reach y=-sy-1 in the next step
    // -> choose sy so that -sy-1 = y_min (this is the maximum sy that still hits the lowest row of the target area)
    const int sy = -y_min - 1;
    // if you launch a missile with vertical speed sy, it will reach a maximum height of sy + (sy-1) + ... + 2 + 1 = sy * (sy+1) / 2
    return sy * (sy + 1) / 2;
}

vector<int> x_velocities(int step, int x_min, int x_max) {
    vector<int> result;
    for (int vx = x_min / step; vx <= x_max; vx++) {
        int x_pos = step >= vx ? vx * (vx + 1) / 2 : step * vx - step * (step - 1) / 2;
        if (x_min <= x_pos && x_pos <= x_max) {
            result.push_back(vx);
        }
    }
    return result;
}

vector<int> y_velocities(int step, int vy_max, int y_min, int y_max) {
    vector<int> result;
    for (int vy = y_min; vy <= vy_max; vy++) {
        int y_pos = step * vy - step * (step - 1) / 2;
        if (y_min <= y_pos && y_pos <= y_max) {
            result.push_back(vy);
        }
    }
    return result;
}

unsigned long day17b(const string& input) {
    vector<int> target_area = find_numbers(input);
    int x_min = target_area.at(0), x_max = target_area.at(1), y_min = target_area.at(2), y_max = target_area.at(3);
    int vy_max = -y_min - 1, step_max = 2*vy_max + 2;
    set<pair<int, int>> velocities;
    for (int step = 1; step <= step_max; step++) {
        for (int vy : y_velocities(step, vy_max, y_min, y_max)) {
            for (int vx : x_velocities(step, x_min, x_max)) {
                velocities.insert(make_pair(vx, vy));
            }
        }
    }
    return velocities.size();
}
