#include <iostream>
#include <vector>

using namespace std;

int day03a(const vector<string>& lines) {
    size_t rows = lines.size(), cols = lines.at(0).length();
    string gamma, epsilon;
    for (int x = 0; x < cols; x++) {
        int one_bits = 0;
        for (const string& line : lines) {
            if (line[x] == '1') {
                one_bits++;
            }
        }
        if (2 * one_bits > rows) {
            gamma += "1";
            epsilon += "0";
        } else if (2 * one_bits < rows) {
            gamma += "0";
            epsilon += "1";
        } else {
            throw invalid_argument("same number of zeros and ones in column " + to_string(x + 1));
        }
    }
    return stoi(gamma, nullptr, 2) * stoi(epsilon, nullptr, 2);
}

vector<string> find_matching(const vector<string>& numbers, int column, bool most_common) {
    vector<string> zeros, ones;
    for (string number : numbers) {
        if (number[column] == '0') zeros.push_back(number); else ones.push_back(number);
    }
    if (zeros.size() <= ones.size()) {
        return most_common ? ones : zeros;
    } else {
        return most_common ? zeros : ones;
    }
}

int find_rating(vector<string> numbers, bool most_common) {
    vector<string> remaining_numbers = numbers;
    for (int x = 0; x < numbers.at(0).length() && remaining_numbers.size() > 1; x++) {
        remaining_numbers = find_matching(remaining_numbers, x, most_common);
    }
    if (remaining_numbers.size() > 1) {
        throw invalid_argument("given numbers did not reduce to a single match after going through all bits");
    }
    return stoi(remaining_numbers.at(0), nullptr, 2);
}

int day03b(const vector<string>& lines) {
    int oxygen_generator_rating = find_rating(lines, true);
    int co2_scrubber_rating = find_rating(lines, false);
    return oxygen_generator_rating * co2_scrubber_rating;
}
