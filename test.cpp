#include <gtest/gtest.h>
#include "day01.cpp"
#include "day02.cpp"
#include "day03.cpp"
#include "day04.cpp"
#include "day05.cpp"
#include "day06.cpp"
#include "day07.cpp"
#include "day08.cpp"
#include "day09.cpp"
#include "day10.cpp"
#include "day11.cpp"
#include "day12.cpp"
#include "day13.cpp"
#include "day14.cpp"
#include "day15.cpp"
#include "day16.cpp"
#include "day17.cpp"

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

TEST(Samples, Day08) {
    vector<string> sample_input = {
            "be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe",
            "edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc",
            "fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg",
            "fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb",
            "aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea",
            "fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb",
            "dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe",
            "bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef",
            "egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb",
            "gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce",
    };
    EXPECT_EQ(day08a(sample_input), 26);
    EXPECT_EQ(day08b(sample_input), 61229);
}

TEST(Samples, Day09) {
    vector<string> sample_input = {
            "2199943210",
            "3987894921",
            "9856789892",
            "8767896789",
            "9899965678",
    };
    EXPECT_EQ(day09a(sample_input), 15);
    EXPECT_EQ(day09b(sample_input), 1134);
}

TEST(Samples, Day10) {
    vector<string> sample_input = {
            "[({(<(())[]>[[{[]{<()<>>",
            "[(()[<>])]({[<{<<[]>>(",
            "{([(<{}[<>[]}>{[]{[(<()>",
            "(((({<>}<{<{<>}{[]{[]{}",
            "[[<[([]))<([[{}[[()]]]",
            "[{[{({}]{}}([{[{{{}}([]",
            "{<[[]]>}<{[{[{[]{()[[[]",
            "[<(<(<(<{}))><([]([]()",
            "<{([([[(<>()){}]>(<<{{",
            "<{([{{}}[<[[[<>{}]]]>[]]",
    };
    EXPECT_EQ(day10a(sample_input), 26397);
    EXPECT_EQ(day10b(sample_input), 288957);
}

TEST(Samples, Day11) {
    vector<string> sample_input = {
            "5483143223",
            "2745854711",
            "5264556173",
            "6141336146",
            "6357385478",
            "4167524645",
            "2176841721",
            "6882881134",
            "4846848554",
            "5283751526",
    };
    EXPECT_EQ(day11a(sample_input), 1656);
    EXPECT_EQ(day11b(sample_input), 195);
}

TEST(Samples, Day12) {
    vector<string> sample_input = {
            "start-A",
            "start-b",
            "A-c",
            "A-b",
            "b-d",
            "A-end",
            "b-end",
    };
    EXPECT_EQ(day12a(sample_input), 10);
    EXPECT_EQ(day12b(sample_input), 36);
}

TEST(Samples, Day13) {
    vector<string> sample_input = {
            "6,10",
            "0,14",
            "9,10",
            "0,3",
            "10,4",
            "4,11",
            "6,0",
            "6,12",
            "4,1",
            "0,13",
            "10,12",
            "3,4",
            "3,0",
            "8,4",
            "1,10",
            "2,14",
            "8,10",
            "9,0",
            "",
            "fold along y=7",
            "fold along x=5",
    };
    EXPECT_EQ(day13a(sample_input), 17);
}

TEST(Samples, Day14) {
    vector<string> sample_input = {
            "NNCB",
            "",
            "CH -> B",
            "HH -> N",
            "CB -> H",
            "NH -> C",
            "HB -> C",
            "HC -> B",
            "HN -> C",
            "NN -> C",
            "BH -> H",
            "NC -> B",
            "NB -> B",
            "BN -> B",
            "BB -> N",
            "BC -> B",
            "CC -> N",
            "CN -> C",
    };
    EXPECT_EQ(day14a(sample_input), 1588);
    EXPECT_EQ(day14b(sample_input), 2188189693529);
}

TEST(Samples, Day15) {
    vector<string> sample_input = {
            "1163751742",
            "1381373672",
            "2136511328",
            "3694931569",
            "7463417111",
            "1319128137",
            "1359912421",
            "3125421639",
            "1293138521",
            "2311944581",
    };
    EXPECT_EQ(day15a(sample_input), 40);
    EXPECT_EQ(day15b(sample_input), 315);
}

TEST(Samples, Day16) {
    EXPECT_EQ(day16a("D2FE28"), 6);
    EXPECT_EQ(day16a("EE00D40C823060"), 14);
    EXPECT_EQ(day16a("8A004A801A8002F478"), 16);
    EXPECT_EQ(day16a("620080001611562C8802118E34"), 12);
    EXPECT_EQ(day16a("C0015000016115A2E0802F182340"), 23);
    EXPECT_EQ(day16a("A0016C880162017C3686B18A3D4780"), 31);

    EXPECT_EQ(day16b("C200B40A82"), 3);
    EXPECT_EQ(day16b("04005AC33890"), 54);
    EXPECT_EQ(day16b("880086C3E88112"), 7);
    EXPECT_EQ(day16b("CE00C43D881120"), 9);
    EXPECT_EQ(day16b("D8005AC2A8F0"), 1);
    EXPECT_EQ(day16b("F600BC2D8F"), 0);
    EXPECT_EQ(day16b("9C005AC2F8F0"), 0);
    EXPECT_EQ(day16b("9C0141080250320F1802104A08"), 1);
}

TEST(Samples, Day17) {
    EXPECT_EQ(day17a("target area: x=20..30, y=-10..-5"), 45);
}
