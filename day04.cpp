#include <utility>
#include <vector>
#include <map>
#include "common.h"

#define SIZE 5
using namespace std;

class Board {
public:
    Board(map<int, pair<short, short>> nums, map<pair<short, short>, int > coords) : num_to_coord(move(nums)), coord_to_num(move(coords)) {}

    static Board from_string(vector<string> lines) {
        map<int, pair<short, short>> num_to_coord {};
        map<pair<short, short>, int > coord_to_num {};
        for (short y = 0; y < SIZE; y++) {
            const vector<string> row = split(lines.at(y), " ");
            for (short x = 0; x < SIZE; x++) {
                const auto coord = make_pair(x, y);
                const int num = stoi(row.at(x));
                num_to_coord[num] = coord;
                coord_to_num[coord] = num;
            }
        }
        return {num_to_coord, coord_to_num};
    }

    int mark_number(int num) {
        if (has_won || num_to_coord.count(num) == 0) {
            return -1;
        }
        auto coord = num_to_coord.at(num);
        coord_to_marked[coord] = true;
        if (!has_bingo(coord)) {
            return -1;
        }
        has_won = true;
        return score(num);

    }

private:
    const map<int, pair<short, short>> num_to_coord {};
    const map<pair<short, short>, int> coord_to_num {};
    map<pair<short, short>, bool> coord_to_marked;
    bool has_won = false;

    int score(int winning_num) {
        int sum_unmarked = 0;
        for (short y = 0; y < SIZE; y++) {
            for (short x = 0; x < SIZE; x++) {
                auto coord = make_pair(x, y);
                if (!coord_to_marked[coord]) {
                    sum_unmarked += coord_to_num.at(coord);
                }
            }
        }
        return sum_unmarked * winning_num;
    }

    bool has_bingo(pair<short, short> coord) {
        return has_bingo_in_col(coord.first) || has_bingo_in_row(coord.second);
    }
    bool has_bingo_in_col(short x) {
        for (short y = 0; y < SIZE; y++) {
            if (!coord_to_marked[make_pair(x, y)]) {
                return false;
            }
        }
        return true;
    }
    bool has_bingo_in_row(short y) {
        for (short x = 0; x < SIZE; x++) {
            if (!coord_to_marked[make_pair(x, y)]) {
                return false;
            }
        }
        return true;
    }
};


vector<Board> parse_boards(const vector<string> &lines) {
    vector<Board> boards;
    int row = 2;
    while (lines.size() > row) {
        Board board = Board::from_string(vector(lines.begin() + row, lines.begin() + row + 5));
        boards.push_back(board);
        row += 6;
    }
    return boards;
}

int day04a(const vector<string>& lines) {
    vector<string> nums = split(lines.at(0), ",");
    vector<Board> boards = parse_boards(lines);
    for (const string& num : nums) {
        for (Board& board : boards) {
            int winning_score = board.mark_number(stoi(num));
            if (winning_score >= 0) {
                return winning_score;
            }
        }
    }
    return -1;
}

int day04b(const vector<string>& lines) {
    vector<string> nums = split(lines.at(0), ",");
    vector<Board> boards = parse_boards(lines);
    int winners = 0;
    for (const string& num : nums) {
        for (Board& board : boards) {
            int winning_score = board.mark_number(stoi(num));
            if (winning_score >= 0) {
                winners++;
                if (winners == boards.size()) {
                    return winning_score;
                }
            }
        }
    }
    return -1;
}
