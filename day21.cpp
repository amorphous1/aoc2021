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
