#include <vector>
#include <string>
#include <map>
#include <climits>

using namespace std;

unsigned long polymer_growth(const vector<string> &lines, const int steps) {
    string polymer_template = lines.at(0);
    map<string, unsigned long> pair_counts;
    for (int i = 0; i < polymer_template.size() - 1; i++) {
        pair_counts[polymer_template.substr(i, 2)]++;
    }
    map<string, string> insertion_rules;
    for (int row = 2; row < lines.size(); row++) {
        const auto& [elements, insertion] = split_pair(lines.at(row), " -> ");
        insertion_rules[elements] = insertion;
    }
    for (int step = 1; step <= steps; step++) {
        map<string, unsigned long> new_pair_counts;
        for (const auto& [existing, count] : pair_counts) {
            string new_element = insertion_rules.at(existing);
            new_pair_counts[existing.at(0) + new_element] += count;
            new_pair_counts[new_element + existing.at(1)] += count;
        }
        pair_counts = new_pair_counts;
    }
    map<char, unsigned long> element_double_counts;
    element_double_counts[polymer_template.at(0)]++;
    element_double_counts[polymer_template.at(polymer_template.size() - 1)]++;
    for (const auto& [elements, count] : pair_counts) {
        element_double_counts[elements.at(0)] += count;
        element_double_counts[elements.at(1)] += count;
    }
    unsigned long min_double_count = LONG_MAX, max_double_count = 0;
    for (const auto& [el, count] : element_double_counts) {
        min_double_count = count < min_double_count ? count : min_double_count;
        max_double_count = count > max_double_count ? count : max_double_count;
    }
    return max_double_count / 2 - min_double_count / 2;
}

unsigned long day14a(const vector<string>& lines) {
    return polymer_growth(lines, 10);
}

unsigned long day14b(const vector<string>& lines) {
    return polymer_growth(lines, 40);
}
