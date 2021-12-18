#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct SnailfishNumber {
    int value;
    SnailfishNumber* left;
    SnailfishNumber* right;

    SnailfishNumber(int v, SnailfishNumber* l, SnailfishNumber* r) {
        value = v;
        left = l;
        right = r;
    }

    void add_to_leftmost_val(int to_add) {
        if (value >= 0) {
            value += to_add;
        } else {
            left->add_to_leftmost_val(to_add);
        }
    }

    void add_to_rightmost_val(int to_add) {
        if (value >= 0) {
            value += to_add;
        } else {
            right->add_to_rightmost_val(to_add);
        }
    }

    bool explode(int depth, pair<int, int>& exploded) {
        if (value >= 0) {
            return false;
        }
        if (depth >= 4 && value < 0) {
            exploded = make_pair(this->left->value, this->right->value);
            this->value = 0;
            delete this->left; this->left = nullptr; // FIXME replace with managed pointers or avoid altogether
            delete this->right; this->right = nullptr;
            return true;
        }
        if (left != nullptr && left->explode(depth + 1, exploded)) {
            if (right != nullptr && exploded.second >= 0) {
                right->add_to_leftmost_val(exploded.second);
                exploded.second = -1;
            }
            return true;
        }
        if (right != nullptr && right->explode(depth + 1, exploded)) {
            if (left != nullptr && exploded.first >= 0) {
                left->add_to_rightmost_val(exploded.first);
                exploded.first = -1;
            }
            return true;
        }
        return false;
    }

    bool split() {
        if (value < 0) {
            return (left != nullptr && left->split()) || (right != nullptr && right->split());
        }
        if (value >= 0 && value < 10) {
            return false;
        }
        this->left = new SnailfishNumber(floor(value / 2.0), nullptr, nullptr);
        this->right = new SnailfishNumber(ceil(value / 2.0), nullptr, nullptr);
        this->value = -1;
        return true;
    }

    SnailfishNumber* reduce() {
        bool changed;
        do {
            pair<int, int> none_exploded = make_pair(-1,-1);
            changed = this->explode(0, none_exploded);
            if (!changed) {
                changed = this->split();
            }
        } while (changed);
        return this;
    }

    SnailfishNumber* add(SnailfishNumber *other) {
        return (new SnailfishNumber(-1, this, other))->reduce();
    }

    unsigned long magnitude() {
        return value >=0 ? value : 3 * left->magnitude() + 2 * right->magnitude();
    }

    static SnailfishNumber* parse_from(const string& str) {
        int start_pos = 0;
        return parse_from(str, start_pos);
    }

    static SnailfishNumber* parse_from(const string& str, int& pos) {
        char ch = str.at(pos++);
        if (isdigit(ch)) {
            return new SnailfishNumber(ch - '0', nullptr, nullptr);
        }
        SnailfishNumber* left = parse_from(str, pos);
        pos++; // skip ','
        SnailfishNumber* right = parse_from(str, pos);
        pos++; // slip ']'
        return new SnailfishNumber(-1, left, right);
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
