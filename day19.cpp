#include <map>
#include <set>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

struct Coord {
    int a, b, c;

    Coord using_orientation(int orientation) {
        switch (orientation) {
            case 0:  return { a, b, c };   case 1:  return { -b, a, c };   case 2:  return { -a, -b, c };  case 3:  return { b, -a, c };
            case 4:  return { -a, b, -c }; case 5:  return { b, a, -c };   case 6:  return { a, -b, -c };  case 7:  return { -b, -a, -c };
            case 8:  return { -a, c, b };  case 9:  return { c, a, b };    case 10: return { a, -c, b };   case 11: return { -c, -a, b };
            case 12: return { a, c, -b };  case 13: return { -c, a, -b };  case 14: return { -a, -c, -b }; case 15: return { c, -a, -b };
            case 16: return { b, c, a };   case 17: return { -c, b, a };   case 18: return { -b, -c, a };  case 19: return { c, -b, a };
            case 20: return { -b, c, -a }; case 21: return { -c, -b, -a }; case 22: return { b, -c, -a };  case 23: return { c, b, -a };
            default: throw invalid_argument("unknown orientation ID " + to_string(orientation));
        }
    }
    Coord subtract(Coord other) const {
        return { other.a - a, other.b - b, other.c - c };
    }
    Coord add(Coord other) const {
        return { other.a + a, other.b + b, other.c + c };
    }
    bool operator==(const Coord& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
    bool operator<(const Coord &other) const {
        return a < other.a || (a == other.a && b < other.b) || (a == other.a && b == other.b && c < other.c);
    }
};

ostream& operator<<(ostream& os, const Coord& c) {
    os << c.a << ',' << c.b << ',' << c.c;
    return os;
}

struct ScannerResult {
    map<int, vector<Coord>> coords;
    int orientation = -1;
    Coord position;

    bool find_match(ScannerResult& other, int min_overlap) {
        vector<Coord> known_coords = coords.at(orientation);
        for (int other_orientation = 0; other_orientation < 24; other_orientation++) {
            map<Coord, int> mappings_by_offset;
            for (Coord coord : coords.at(orientation)) {
                for (Coord other_coord : other.coords.at(other_orientation)) {
                    Coord current_offset = other_coord.subtract(coord);
                    mappings_by_offset[current_offset]++;
                    if (mappings_by_offset[current_offset] >= min_overlap) {
                        other.orientation = other_orientation;
                        other.position = position.add(current_offset);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void find_matches(vector<ScannerResult>& scanner_results, set<int>& scanners_to_check) {
        for (int i = 0; i < scanner_results.size(); i++) {
            if (scanner_results.at(i).orientation < 0 && find_match(scanner_results.at(i), 12)) {
                scanners_to_check.insert(i);
            }
        }
    }

    static map<int, vector<Coord>> coords_by_orientation(const vector<Coord>& scanned_coords) {
        map<int, vector<Coord>> result = {};
        for (int orientation = 0; orientation < 24; orientation++) {
            vector<Coord> coords = {};
            for (Coord coord : scanned_coords) {
                coords.push_back(coord.using_orientation(orientation));
            }
            result.insert({ orientation, coords });
        }
        return result;
    }
};

ostream& operator<<(ostream& os, const ScannerResult& s) {
    os << "{ pos=" << s.position << ", orientation=" << s.orientation << " }";
    return os;
}


unsigned long day19a(const vector<string>& lines) {
    vector<ScannerResult> scanner_results;
    vector<Coord> coords;
    for (const string& line : lines) {
        if (line.empty()) {
            continue;
        } else if (line.starts_with("--- scanner")) {
            if (!coords.empty()) {
                scanner_results.push_back({ScannerResult::coords_by_orientation(coords) });
            }
            coords = {};
        } else {
            vector<int> numbers = find_numbers(line);
            coords.push_back({ numbers.at(0), numbers.at(1), numbers.at(2) });
        }
    }
    scanner_results.push_back({ScannerResult::coords_by_orientation(coords) });

    scanner_results.at(0).orientation = 0;
    scanner_results.at(0).position = {0, 0, 0};
    set<int> scanners_to_check = { 0 };

    while (!scanners_to_check.empty()) {
        int current_idx = *scanners_to_check.begin();
        ScannerResult current = scanner_results.at(current_idx);
        scanners_to_check.erase(current_idx);
        current.find_matches(scanner_results, scanners_to_check);
    }

    set<Coord> all_coords;
    for (ScannerResult scanner_result : scanner_results) {
        for (Coord coord : scanner_result.coords.at(scanner_result.orientation)) {
            all_coords.insert(scanner_result.position.add(coord));
        }
    }
    return all_coords.size();
}