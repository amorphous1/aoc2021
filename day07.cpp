#include <numeric>
#include <cmath>

int day07a(vector<int> positions) {
    sort(positions.begin(), positions.end());
    const int target_position = positions.at(positions.size() / 2);
    int fuel_spent = 0;
    for (const int position : positions) {
        fuel_spent += abs(position - target_position);
    }
    return fuel_spent;
}

int day07b(vector<int> positions) {
    const int target_position_1 = accumulate(positions.begin(), positions.end(), 0, plus<>()) / (int)positions.size();
    const int target_position_2 = target_position_1 + 1;
    int fuel_spent_1 = 0, fuel_spent_2 = 0;
    for (const int position : positions) {
        const int delta_1 = abs(target_position_1 - position), delta_2 = abs(target_position_2 - position);
        fuel_spent_1 += delta_1 * (delta_1 + 1) / 2;
        fuel_spent_2 += delta_2 * (delta_2 + 1) / 2;
    }
    return min(fuel_spent_1, fuel_spent_2);
}
