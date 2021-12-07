#include <gtest/gtest.h>
#include "day01.cpp"
#include "day02.cpp"
#include "day03.cpp"
#include "day04.cpp"
#include "day05.cpp"
#include "day06.cpp"
#include "day07.cpp"

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

TEST(Samples, Day03) {
    vector<string> sample_input = { "00100", "11110", "10110", "10111", "10101", "01111", "00111", "11100", "10000", "11001", "00010", "01010" };
    EXPECT_EQ(day03a(sample_input), 198);
    EXPECT_EQ(day03b(sample_input), 230);
}

TEST(Samples, Day04) {
    vector<string> sample_input = {
            "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
            "",
            "22 13 17 11  0",
            "8  2 23  4 24",
            "21  9 14 16  7",
            "6 10  3 18  5",
            "1 12 20 15 19",
            "",
            "3 15  0  2 22",
            "9 18 13 17  5",
            "19  8  7 25 23",
            "20 11 10 24  4",
            "14 21 16 12  6",
            "",
            "14 21 17 24  4",
            "10 16 15  9 19",
            "18  8 23 26 20",
            "22 11 13  6  5",
            "2  0 12  3  7",
};
    EXPECT_EQ(day04a(sample_input), 4512);
    EXPECT_EQ(day04b(sample_input), 1924);
}

TEST(Samples, Day05) {
    vector<string> sample_input = {
            "0,9 -> 5,9",
            "8,0 -> 0,8",
            "9,4 -> 3,4",
            "2,2 -> 2,1",
            "7,0 -> 7,4",
            "6,4 -> 2,0",
            "0,9 -> 2,9",
            "3,4 -> 1,4",
            "0,0 -> 8,8",
            "5,5 -> 8,2",
    };
    EXPECT_EQ(day05a(sample_input), 5);
    EXPECT_EQ(day05b(sample_input), 12);
}

TEST(Samples, Day06) {
    vector<int> sample_input = { 3,4,3,1,2 };
    EXPECT_EQ(day06a(sample_input), 5934);
    EXPECT_EQ(day06b(sample_input), 26984457539);
}

TEST(Samples, Day07) {
    vector<int> sample_input = { 16,1,2,0,4,2,7,1,2,14 };
    EXPECT_EQ(day07a(sample_input), 37);
    EXPECT_EQ(day07b(sample_input), 168);
}