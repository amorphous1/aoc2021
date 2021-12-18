#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <iostream>

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
            assert(exploded.first >= 0 && exploded.second >= 0);
            this->value = 0;
            this->left = nullptr;
            this->right = nullptr;
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
            cout << repr() ;
            changed = this->explode(0, none_exploded);
            cout << " -> " << (changed ? repr() : "unchanged");
            if (!changed) {
                changed = this->split();
                cout << " -> " << (changed ? repr() : "unchanged");
            }
            cout << endl;
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
        assert(ch == '[');
        SnailfishNumber* left = parse_from(str, pos);
        assert(str.at(pos) == ',');
        pos++;
        SnailfishNumber* right = parse_from(str, pos);
        assert(str.at(pos) == ']');
        pos++;
        return new SnailfishNumber(-1, left, right);
    }

    string repr() {
        return value >= 0 ? to_string(value) : "[" + left->repr() + "," + right->repr() + "]";
    }
};

unsigned long day18a(const vector<string>& lines) {
    SnailfishNumber* result = SnailfishNumber::parse_from(lines.at(0));
    for (int i = 1; i < lines.size(); i++) {
        SnailfishNumber* next = SnailfishNumber::parse_from(lines.at(i));
        result = result->add(next);
        cout << "----- result after step " << i << ": " << result->repr() << endl << endl;
    }
    return result->magnitude();
}
