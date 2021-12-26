#include <map>
#include <set>
#include <string>
#include <vector>
#include "common.h"
using namespace std;

unsigned long day21a(const vector<string>& lines) {
    map<int, int> position, score;
    for (const string& line : lines) {
        vector<int> player_and_pos = find_numbers(line);
        position[player_and_pos.at(0)] = player_and_pos.at(1) - 1; // make position 0-based
        score[player_and_pos.at(0)] = 0;
    }
    int player = 1, last_die_roll = 0;
    while (score[1] < 1000 && score[2] < 1000) {
        int total_roll = (last_die_roll + 1) + (last_die_roll + 2) + (last_die_roll + 3);
        last_die_roll += 3;
        position[player] = (position[player] + total_roll) % 10;
        score[player] += position[player] + 1;
        player = player == 1 ? 2 : 1;
    }
    return last_die_roll * min(score[1], score[2]);
}

const map<int, unsigned long> dirac_die_roll_counts = { {3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1} };

struct DiracGameState {
    int pos1, score1, pos2, score2;

    bool operator<(const DiracGameState &other) const {
        return (score1 < other.score1) || (score1 == other.score1 && score2 < other.score2) ||
               (score1 == other.score1 && score2 == other.score2 && pos1 < other.pos1) ||
               (score1 == other.score1 && score2 == other.score2 && pos1 == other.pos1 && pos2 < other.pos2);
    }
};

pair<unsigned long, unsigned long> find_wins_from(
        const DiracGameState& state, map<DiracGameState, pair<unsigned long, unsigned long>>& wins_by_state) {
    if (wins_by_state.contains(state)) {
        return wins_by_state.at(state);
    }
    unsigned long wins1 = 0, wins2 = 0;
    for (const auto& [roll1, count1] : dirac_die_roll_counts) {
        int new_pos1 = (state.pos1 + roll1) % 10, new_score1 = state.score1 + new_pos1 + 1;
        if (new_score1 >= 21) {
            wins1 += count1;
        } else {
            for (const auto& [roll2, count2]: dirac_die_roll_counts) {
                int new_pos2 = (state.pos2 + roll2) % 10, new_score2 = state.score2 + new_pos2 + 1;
                if (new_score2 >= 21) {
                    wins2 += count1 * count2;
                } else {
                    auto [new_p1_wins, new_p2_wins] = find_wins_from({new_pos1, new_score1, new_pos2, new_score2}, wins_by_state);
                    wins1 += new_p1_wins * count1 * count2;
                    wins2 += new_p2_wins * count1 * count2;
                }
            }
        }
    }
    wins_by_state[state] = make_pair(wins1, wins2);
    return make_pair(wins1, wins2);
}

unsigned long day21b(const vector<string>& lines) {
    const DiracGameState start_state = { find_numbers(lines.at(0)).at(1) - 1, 0, find_numbers(lines.at(1)).at(1) - 1, 0 };
    map<DiracGameState, pair<unsigned long, unsigned long>> wins_by_state;
    const auto wins = find_wins_from(start_state, wins_by_state);
    return max(wins.first, wins.second);
}