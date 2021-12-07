#pragma once
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

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

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
