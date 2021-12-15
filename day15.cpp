#include <vector>
#include <string>
#include <map>
#include <set>

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

unsigned long min_risk(const map<pair<int, int>, unsigned long> &risk, const int max_idx) {
    map<pair<int, int>, unsigned long> min_total_risk;
    for (int y = max_idx; y >= 0; y--) {
        for (int x = max_idx; x >= 0; x--) {
            if (x == max_idx && y == max_idx) {
                min_total_risk[make_pair(x, y)] = risk.at(make_pair(x, y));
            } else if (x == max_idx) {
                min_total_risk[make_pair(x, y)] = risk.at(make_pair(x, y)) + min_total_risk[make_pair(x, y + 1)];
            } else if (y == max_idx) {
                min_total_risk[make_pair(x, y)] = risk.at(make_pair(x, y)) + min_total_risk[make_pair(x + 1, y)];
            } else {
                min_total_risk[make_pair(x, y)] = risk.at(make_pair(x, y)) + min(min_total_risk[make_pair(x + 1, y)], min_total_risk[make_pair(x, y + 1)]);
            }
        }
    }
    return min_total_risk.at(make_pair(0, 0)) - risk.at(make_pair(0, 0));
}

unsigned long day15a(const vector<string>& lines) {
    map<pair<int, int>, unsigned long> risk = parse_risk_levels(lines, 0);
    return min_risk(risk, (int)lines.size() - 1);
}

unsigned long day15b(const vector<string>& lines) {
    map<pair<int, int>, unsigned long> risk = parse_risk_levels(lines, 4);
    return min_risk(risk, (int)(5 * lines.size() - 1));
}
