#pragma once
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    if (delimiter.empty()) {
        for (char c: s) {
            token = string(1, c);
            res.push_back(token);
        }
        return res;
    }

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (!token.empty()) {
            res.push_back(token);
        }
    }
    res.push_back(s.substr(pos_start));
    return res;
}

pair<string, string> split_pair(const string& s, const string& delimiter) {
    vector<string> splits = split(s, delimiter);
    if (splits.size() != 2) {
        throw invalid_argument("'" + s + "' does not split in exactly two parts using delimiter '" + delimiter + "'");
    }
    return make_pair(splits.at(0), splits.at(1));
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

vector<int> ints(const vector<string>& numbers) {
    vector<int> result;
    result.resize(numbers.size() ); // unfortunately this is necessary
    transform(numbers.begin(), numbers.end(), result.begin(), [](const string& s) { return stoi(s); });
    return result;
}