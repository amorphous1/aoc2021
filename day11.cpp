#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

map<pair<int, int>, int> parse_energies(const vector<string> &lines) {
    map<pair<int, int>, int> energy_by_pos;
    for (int y = 0; y < lines.size(); y++) {
        vector<string> energies = split(lines.at(y), "");
        for (int x = 0; x < energies.size(); x++) {
            energy_by_pos[make_pair(x,y)] = stoi(energies.at(x));
        }
    }
    return energy_by_pos;
}

int count_flashes(map<pair<int, int>, int> &energy_by_pos) {
    int num_flashes = 0;
    set<pair<int, int>> to_be_checked;
    for (const auto& [pos, energy] : energy_by_pos) {
        energy_by_pos[pos]++;
        to_be_checked.insert(pos);
    }
    while (!to_be_checked.empty()) {
        pair<int, int> current = *to_be_checked.begin();
        to_be_checked.erase(current);
        if (energy_by_pos.at(current) > 9) {
            energy_by_pos[current] = 0;
            num_flashes++;
            int x = current.first, y = current.second;
            for (const auto& neighbour : { make_pair(x-1, y-1), make_pair(x, y-1), make_pair(x+1, y-1),
                                          make_pair(x-1, y),                       make_pair(x+1, y),
                                          make_pair(x-1, y+1),  make_pair(x, y+1), make_pair(x+1, y+1) }) {
                if (energy_by_pos.contains(neighbour) && energy_by_pos.at(neighbour) > 0) {
                    energy_by_pos[neighbour]++;
                    to_be_checked.insert(neighbour);
                }
            }
        }
    }
    return num_flashes;
}

long day11a(const vector<string>& lines) {
    map<pair<int, int>, int> energy_by_pos = parse_energies(lines);
    int num_flashes = 0;
    for (int day = 1; day <= 100; day++) {
        num_flashes += count_flashes(energy_by_pos);
    }
    return num_flashes;
}

long day11b(const vector<string>& lines) {
    map<pair<int, int>, int> energy_by_pos = parse_energies(lines);
    for (int day = 1; ; day++) {
        if (count_flashes(energy_by_pos) == energy_by_pos.size()) {
            return day;
        }
    }
}
