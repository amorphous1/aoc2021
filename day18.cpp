#include <vector>
#include <string>
#include <cmath>
#define BRANCH_NODE -1

using namespace std;

struct SnailfishNumber {
    int value;
    SnailfishNumber* left;
    SnailfishNumber* right;

    void add_to_leftmost_leaf(int to_add) {
        if (value == BRANCH_NODE) {
            left->add_to_leftmost_leaf(to_add);
        } else {
            value += to_add;
        }
    }

    void add_to_rightmost_leaf(int to_add) {
        if (value == BRANCH_NODE) {
            right->add_to_rightmost_leaf(to_add);
        } else {
            value += to_add;
        }
    }

    bool explode(int depth, pair<int, int>& exploded) {
        if (value != BRANCH_NODE) {
            return false;
        }
        if (depth == 4) {
            exploded = make_pair(left->value, right->value);
            value = 0;
            delete left; left = nullptr; // FIXME replace with managed pointers or avoid altogether
            delete right; right = nullptr;
            return true;
        }
        if (left != nullptr && left->explode(depth + 1, exploded)) {
            if (right != nullptr && exploded.second >= 0) {
                right->add_to_leftmost_leaf(exploded.second);
                exploded.second = -1;
            }
            return true;
        }
        if (right != nullptr && right->explode(depth + 1, exploded)) {
            if (left != nullptr && exploded.first >= 0) {
                left->add_to_rightmost_leaf(exploded.first);
                exploded.first = -1;
            }
            return true;
        }
        return false;
    }

    bool split() {
        if (value == BRANCH_NODE) {
            return (left != nullptr && left->split()) || (right != nullptr && right->split());
        }
        if (value >= 0 && value <= 9) {
            return false;
        }
        left = new SnailfishNumber { (int)floor(value / 2.0) };
        right = new SnailfishNumber { (int)ceil(value / 2.0) };
        value = BRANCH_NODE;
        return true;
    }

    SnailfishNumber* add(SnailfishNumber* other) {
        auto* sum = new SnailfishNumber { BRANCH_NODE, this, other };
        bool changed;
        do {
            pair<int, int> none_exploded = make_pair(-1, -1);
            changed = sum->explode(0, none_exploded) || sum->split();
        } while (changed);
        return sum;
    }

    unsigned long magnitude() {
        return value == BRANCH_NODE ? 3 * left->magnitude() + 2 * right->magnitude() : value;
    }

    static SnailfishNumber* parse_from(const string& str) {
        int start_pos = 0;
        return parse_from(str, start_pos);
    }

    static SnailfishNumber* parse_from(const string& str, int& pos) {
        char ch = str.at(pos++);
        if (isdigit(ch)) {
            return new SnailfishNumber { ch - '0' };
        }
        SnailfishNumber* left = parse_from(str, pos);
        pos++; // skip ','
        SnailfishNumber* right = parse_from(str, pos);
        pos++; // skip ']'
        return new SnailfishNumber { -1, left, right };
    }
};

unsigned long day18a(const vector<string>& lines) {
    SnailfishNumber* result = SnailfishNumber::parse_from(lines.at(0));
    for (int i = 1; i < lines.size(); i++) {
        result = result->add(SnailfishNumber::parse_from(lines.at(i)));
    }
    return result->magnitude();
}

unsigned long day18b(const vector<string>& lines) {
    unsigned long max_magnitude = 0;
    for (int a = 0; a < lines.size(); a++) {
        for (int b = 0; b < lines.size(); b++) {
            if (a != b) {
                auto magnitude = SnailfishNumber::parse_from(lines.at(a))->add(SnailfishNumber::parse_from(lines.at(b)))->magnitude();
                max_magnitude = max(magnitude, max_magnitude);
            }
        }
    }
    return max_magnitude;
}