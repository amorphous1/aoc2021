#include <vector>
#include <string>
#include <map>
#include <set>
#include <climits>

using namespace std;

map<pair<int, int>, unsigned long> parse_risk_levels(const vector<string>& lines, int additional_tiles) {
    map<pair<int, int>, unsigned long> risk;
    int n = (int) lines.size();
    for (int dy = 0; dy <= additional_tiles; dy++) {
        for (int dx = 0; dx <= additional_tiles; dx++) {
            for (int y = 0; y < n; y++) {
                for (int x = 0; x < n; x++) {
                    pair<int, int> pos = make_pair(x + dx*n, y + dy*n);
                    risk[pos] = ((lines.at(y).at(x) - '0') + dx + dy - 1) % 9 + 1;
                }
            }
        }
    }
    return risk;
}

unsigned long total_risk(const pair<int, int>& pos, const map<pair<int, int>, unsigned long>& risk, map<pair<int, int>, unsigned long>& min_total_risk ) {
    return (risk.contains(pos) && min_total_risk.contains(pos)) ? risk.at(pos) + min_total_risk.at(pos) : ULONG_MAX;
}

unsigned long find_min_risk(const map<pair<int, int>, unsigned long>& risk, int max_idx) {
    map<pair<int, int>, unsigned long> min_total_risk;
    bool min_total_risk_changed;
    do {
        min_total_risk_changed = false;
        for (int y = max_idx; y >= 0; y--) {
            for (int x = max_idx; x >= 0; x--) {
                pair<int, int> pos = make_pair(x, y);
                unsigned long old_min_total_risk = min_total_risk.contains(pos) ? min_total_risk.at(pos) : ULONG_MAX;
                unsigned long new_min_total_risk = (x == max_idx && y == max_idx) ? 0 : min(
                        min(total_risk(make_pair(x - 1, y), risk, min_total_risk),
                            total_risk(make_pair(x + 1, y), risk, min_total_risk)),
                        min(total_risk(make_pair(x, y - 1), risk, min_total_risk),
                            total_risk(make_pair(x, y + 1), risk, min_total_risk))
                    );
                if (new_min_total_risk < old_min_total_risk) {
                    min_total_risk_changed = true;
                    min_total_risk[pos] = new_min_total_risk;
                }
            }
        }
    } while (min_total_risk_changed);
    return min_total_risk.at(make_pair(0, 0));
}

unsigned long day15a(const vector<string>& lines) {
    map<pair<int, int>, unsigned long> risk = parse_risk_levels(lines, 0);
    return find_min_risk(risk, (int)lines.size() - 1);
}

unsigned long day15b(const vector<string>& lines) {
    map<pair<int, int>, unsigned long> risk = parse_risk_levels(lines, 4);
    return find_min_risk(risk, (int)(5 * lines.size() - 1));
}
