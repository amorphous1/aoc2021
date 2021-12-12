#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

set<vector<string>> find_paths(const map<string, set<string>>& connections, const string& from, const string& to, set<string> visited) {
    set<vector<string>> result = {};
    visited.insert(from);
    if (from == to) {
        result.insert({from});
    }
    for (const string& neighbour : connections.at(from)) {
        if (!visited.contains(neighbour) || isupper(neighbour[0])) {
            for (vector<string> neighbour_path : find_paths(connections, neighbour, to, visited)) {
                neighbour_path.insert(neighbour_path.begin(), from);
                result.insert(neighbour_path);
            }
        }
    }
    return result;
}

unsigned long day12a(const vector<string>& lines) {
    map<string, set<string>> connections;
    for (const string& line : lines) {
        vector<string> locations = split(line, "-");
        connections[locations.at(0)].insert(locations.at(1));
        connections[locations.at(1)].insert(locations.at(0));
    }
    return find_paths(connections, "start", "end", {}).size();
}
