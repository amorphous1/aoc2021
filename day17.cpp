#include <vector>
#include <string>

using namespace std;

unsigned long day17a(const string& input) {
    int y_min = find_numbers(input).at(2);
    // if you launch a missile with vertical speed sy, it will come back to the x-axis (y=0) with speed -sy, then reach y=-sy-1 in the next step
    // -> choose sy so that -sy-1 = y_min (this is the maximum sy that still hits the lowest row of the target area)
    const int sy = -y_min - 1;
    // if you launch a missile with vertical speed sy, it will reach a maximum height of sy + (sy-1) + ... + 2 + 1 = sy * (sy+1) / 2
    return sy * (sy + 1) / 2;
}
