#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;

const map<char, char> open_to_close = { {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'} };
const map<char, char> close_to_open = { {')', '('}, {']', '['}, {'}', '{'}, {'>', '<'} };

int day10a(const vector<string>& lines) {
    const map<char, int> points = { {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137} };
    int syntax_error_score = 0;
    for (const string& line : lines) {
        stack<char> chunks;
        for (char c : line) {
            if (close_to_open.contains(c)) {
                if (chunks.top() == close_to_open.at(c)) {
                    chunks.pop();
                } else {
                    syntax_error_score += points.at(c);
                    break;
                }
            } else {
                chunks.push(c);
            }
        }
    }
    return syntax_error_score;
}

void score_line(const string &line, vector<unsigned long> &completion_scores) {
    const map<char, unsigned long> completion_points = { {')', 1}, {']', 2}, {'}', 3}, {'>', 4} };
    stack<char> chunks;
    for (char c : line) {
        if (close_to_open.contains(c)) {
            if (chunks.top() == close_to_open.at(c)) {
                chunks.pop();
            } else {
                return;
            }
        } else {
            chunks.push(c);
        }
    }
    if (!chunks.empty()) {
        unsigned long score = 0;
        while (!chunks.empty()) {
            char close = open_to_close.at(chunks.top());
            chunks.pop();
            score = 5 * score + completion_points.at(close);
        }
        completion_scores.push_back(score);
    }
}

unsigned long day10b(const vector<string>& lines) {
    vector<unsigned long> completion_scores;
    for (const string& line : lines) {
        score_line(line, completion_scores);
    }
    sort(completion_scores.begin(), completion_scores.end());
    return completion_scores.at(completion_scores.size() / 2);
}
