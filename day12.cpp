#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

set<vector<string>> find_paths(const map<string, set<string>>& connections, const string& from, const string& to, set<string> visited, const string& may_visit_twice) {
    set<vector<string>> result = {};
    visited.insert(from);
    if (from == to) {
        result.insert({from});
    }
    for (const string& neighbour : connections.at(from)) {
        if (isupper(neighbour[0]) || !visited.contains(neighbour) || neighbour == may_visit_twice) {
            const string new_may_visit_twice = visited.contains(neighbour) && neighbour == may_visit_twice ? "" : may_visit_twice;
            for (vector<string> neighbour_path : find_paths(connections, neighbour, to, visited, new_may_visit_twice)) {
                neighbour_path.insert(neighbour_path.begin(), from);
                result.insert(neighbour_path);
            }
        }
    }
    return result;
}

map<string, set<string>> parse_connections(const vector<string> &lines) {
    map<string, set<string>> connections;
    for (const string& line : lines) {
        vector<string> locations = split(line, "-");
        connections[locations.at(0)].insert(locations.at(1));
        connections[locations.at(1)].insert(locations.at(0));
    }
    return connections;
}

unsigned long day12a(const vector<string>& lines) {
    return find_paths(parse_connections(lines), "start", "end", {}, "").size();
}

unsigned long day12b(const vector<string>& lines) {
    const map<string, set<string>>& connections = parse_connections(lines);
    set<vector<string>> paths;
    for (const auto& [location, _] : connections) {
        if (islower(location[0]) && !(location == "start")  && !(location == "end")) {
            set<vector<string>> new_paths = find_paths(connections, "start", "end", {}, location);
            paths.insert(new_paths.begin(), new_paths.end());
        }
    }
    return paths.size();
}
