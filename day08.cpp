#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

int day08a(const vector<string>& lines) {
    int result = 0;
    set<int> unique_lengths = { 2, 3, 4, 7 };
    for (const string& line : lines) {
        string output_values = split(line, " | ").at(1);
        for (const string& output_value : split(output_values, " ")) {
            if (unique_lengths.contains((int)output_value.size())) {
                result++;
            }
        }
    }
    return result;
}

map<vector<int>, char> fingerprint(const vector<string>& patterns) {
    map<vector<int>, char> result;
    for (char segment = 'a'; segment <= 'g'; segment++) {
        vector<int> fingerprint;
        for (const string& pattern : patterns) {
            if (pattern.find(segment) != string::npos) {
                fingerprint.push_back((int)pattern.length());
            }
        }
        sort(fingerprint.begin(), fingerprint.end());
        result[fingerprint] = segment;
    }
    return result;
}

int day08b(const vector<string>& lines) {
    vector<string> segments = {"abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg"};
    const map<vector<int>, char> fingerprints = fingerprint(segments);
    int result = 0;

    for (const string& line : lines) {
        const vector<string> patterns_outputs = split(line, " | ");
        const vector<string> patterns = split(patterns_outputs.at(0), " ");
        const vector<string> outputs = split(patterns_outputs.at(1), " ");

        map<char, char> unscrambled;
        for (const auto& [fingerprint, scrambled_segment] : fingerprint(patterns)) {
            unscrambled[scrambled_segment] = fingerprints.at(fingerprint);
        }
        string decoded_number;
        for (const string& digit_segments : outputs) {
            string unscrambled_segments;
            for (char segment : digit_segments) {
                unscrambled_segments += unscrambled[segment];
            }
            sort(unscrambled_segments.begin(), unscrambled_segments.end());
            auto itr = std::find(segments.begin(), segments.end(), unscrambled_segments);
            decoded_number += to_string(distance(segments.begin(), itr));
        }
        result += stoi(decoded_number);
    }
    return result;
}
