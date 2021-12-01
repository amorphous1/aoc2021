#include <gtest/gtest.h>
#include "day01.cpp"

using namespace std;

TEST(Samples, Day01) {
    vector<int> sample_input = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
    EXPECT_EQ(day01a(sample_input), 7);
    EXPECT_EQ(day01b(sample_input), 5);
}
