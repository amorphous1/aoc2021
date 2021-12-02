#include <gtest/gtest.h>
#include "day01.cpp"
#include "day02.cpp"

using namespace std;

TEST(Samples, Day01) {
    vector<int> sample_input = { 199, 200, 208, 210, 200, 207, 240, 269, 260, 263 };
    EXPECT_EQ(day01a(sample_input), 7);
    EXPECT_EQ(day01b(sample_input), 5);
}

TEST(Samples, Day02) {
    vector<string> sample_input = { "forward 5", "down 5", "forward 8", "up 3", "down 8", "forward 2" };
    EXPECT_EQ(day02a(sample_input), 150);
    EXPECT_EQ(day02b(sample_input), 900);
}
