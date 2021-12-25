#include <map>
#include <string>
#include <vector>

using namespace std;

/*
    inp w
mul x 0
add x z
mod x 26                x = z % 26
    div z 1             z = z div v1{1,26}
    add x 11            x = x + v2{-1,-2,-7,-8,-13,10,11,12,13,14,15
eql x w
eql x 0                 x = (x != w)
mul y 0
add y 25
mul y x
add y 1                 y = 25 * x + 1
mul z y                 z = z * y = z * (25 * x + 1)
mul y 0
add y w
    add y 5             y = w + v3{1,2,5,6,7,8,12,13,14,15}
mul y x                 y = x * (w + v3)
add z y                 z = z + x * (w + v3)
 */
int step(const int z, const int w, const int v1, const int v2, const int v3) {
    const int x = (z % 26 + v2 != w);
    return (z / v1) * (25 * x + 1) + x * (w + v3);
}

string find_best_code(const int section, const int z, const map<int, vector<int>>& vars, const vector<int>& ws_to_try) {
    int v1 = vars.at(section).at(0), v2 = vars.at(section).at(1), v3 = vars.at(section).at(2);
    if (section == 13) {  // last section, check that z is zero
        int w = (z % 26) + v2;
        return w >= 1 && w <=9 && step(z, w, v1, v2, v3) == 0 ? to_string(w) : "";
    }
    if (v2 < 10) {
        int w = (z % 26) + v2; // calculate w so that x==0 (which in turn minimises z)
        if (w < 1 || w > 9) {
            return "";
        }
        string best = find_best_code(section + 1, step(z, w, v1, v2, v3), vars, ws_to_try);
        return best.empty() ? "" : to_string(w) + best;
    }
    for (int w : ws_to_try) {
        string best = find_best_code(section + 1, step(z, w, v1, v2, v3), vars, ws_to_try);
        if (!best.empty()) {
            return to_string(w) + best;
        }
    }
    return "";
}

map<int, vector<int>> parse_alu_vars(vector<string> &lines) {
    map<int, vector<int>> vars_by_section;
    for (int section = 0; section < 14; section++) {
        vars_by_section[section] = (vector<int>) {
                find_numbers(lines.at(18 * section + 4)).at(0),
                find_numbers(lines.at(18 * section + 5)).at(0),
                find_numbers(lines.at(18 * section + 15)).at(0)
        };
    }
    return vars_by_section;
}

string day24a(vector<string> lines) {
    return find_best_code(0, 0, parse_alu_vars(lines), {9,8,7,6,5,4,3,2,1});
}

string day24b(vector<string> lines) {
    return find_best_code(0, 0, parse_alu_vars(lines), {1,2,3,4,5,6,7,8,9});
}
