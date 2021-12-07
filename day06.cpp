#include <numeric>
#include "common.h"

unsigned long lanternfish_after(int days, const vector<int>& input) {
    unsigned long previous[9] = { 0 }, current[9] = { 0 };
    for (const int timer_val : input) {
        previous[timer_val]++;
    }
    for (int day = 1; day <= days; day++) {
        for (int timer_val = 1; timer_val <= 8; timer_val++) {
            current[timer_val - 1] = previous[timer_val];
        }
        current[6] += previous[0];
        current[8] = previous[0];
        copy(begin(current), end(current), begin(previous));
    }
    return accumulate(begin(current), end(current), 0L, plus<>());
}

unsigned long day06a(const vector<int>& input) {
    return lanternfish_after(80, input);
}

unsigned long day06b(const vector<int>& input) {
    return lanternfish_after(256, input);
}