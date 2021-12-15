#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

unsigned long day15a(const vector<string>& lines) {
    map<pair<int, int>, unsigned long> risk, min_total_risk;
    int max_idx = (int)lines.size() - 1;
    for (int y = 0; y <= max_idx; y++) {
        for (int x = 0; x <= max_idx; x++) {
            risk[make_pair(x, y)] = lines.at(y).at(x) - '0';
        }
    }
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
            cout << x << "," << y << " -> " << min_total_risk[make_pair(x, y)] << "  ";
        }
        cout << endl;
    }
    return min_total_risk.at(make_pair(0, 0)) - risk.at(make_pair(0, 0));
}
