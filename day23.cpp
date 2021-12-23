#include <map>
#include <string>
#include <iostream>

using namespace std;

void output(map<string, char> burrow, map<char, int> moves) {
    cout << endl << "12345678901  A:" << moves['A'] << " B:" << moves['B'] << " C:" << moves['C'] << " D:" << moves['D'] << endl;
    for (int col = 1; col <= 11; col++) {
        cout << burrow.at("h" + to_string(col));
    }
    cout << endl;
    for (int row = 1; row <= 4; row++) {
        cout << "  " << burrow.at("a" + to_string(row)) << " " << burrow.at("b" + to_string(row)) <<
                " " << burrow.at("c" + to_string(row)) << " " << burrow.at("d" + to_string(row)) << endl;
    }
}

int burrow_distance(string loc1, string loc2) {
    if (loc1 > loc2) {
        return burrow_distance(loc2, loc1);
    }
    char type1 = loc1.at(0), type2 = loc2.at(0);
    int num1 = stoi(loc1.substr(1)), num2 = stoi(loc2.substr(1));
    if (type1 == type2) {
        return abs(num2 - num1);
    }
    if (type2 == 'h') {
        string hallway_connection = "h" + to_string(2 * (type1 - 'a') + 3);
        return burrow_distance(string() + type1 + '1', loc1) + 1 + burrow_distance(hallway_connection, loc2);
    }
    return burrow_distance(string() + type1 + '1', loc1) + 1 +
           burrow_distance(string() + type2 + '1', loc2) + 1 + 2 * (type2 - type1);
}

pair<string, string> validate(string input, map<string, char> burrow) {
    vector<string> locs = split(input, " ");
    if (locs.size() != 2) {
        cerr << "Need exactly two locations, separated by space" << endl;
        return make_pair("invalid", "invalid");
    }
    string loc1 = locs.at(0), loc2 = locs.at(1);
    if (!burrow.contains(loc1) || !burrow.contains(loc2)) {
        cerr << "Unknown location, needs to be one of h1 ... h11, a1 ... a4, ..., d1 ... d4" << endl;
        return make_pair("invalid", "invalid");
    }
    if (burrow[loc1] == '.') {
        cerr << "Start location is empty" << endl;
        return make_pair("invalid", "invalid");
    }
    if (burrow[loc2] != '.') {
        cerr << "Target location is not empty" << endl;
        return make_pair("invalid", "invalid");
    }
    return make_pair(loc1, loc2);
}

bool process_move(string &input, map<string, char> &burrow, map<char, int> &moves) {
    const auto [loc1, loc2] = validate(input, burrow);
    if (loc1 != loc2) {
        burrow[loc2] = burrow[loc1];
        burrow[loc1] = '.';
        moves[burrow[loc2]] += burrow_distance(loc1, loc2);
    }
    return loc1 != loc2;
}

void day23b() {
    map<string, char> burrow = {
            {"h1",'.'}, {"h2",'.'}, {"h3",'.'}, {"h4",'.'}, {"h5",'.'}, {"h6",'.'}, {"h7",'.'}, {"h8",'.'}, {"h9",'.'}, {"h10",'.'}, {"h11",'.'},
                                    {"a1",'A'},             {"b1",'D'},             {"c1",'A'},             {"d1",'B'},
                                    {"a2",'D'},             {"b2",'C'},             {"c2",'B'},             {"d2",'A'},
                                    {"a3",'D'},             {"b3",'B'},             {"c3",'A'},             {"d3",'C'},
                                    {"a4",'B'},             {"b4",'C'},             {"c4",'D'},             {"d4",'C'},
    };
    map<char, int> moves = { {'A',0}, {'B',0}, {'C',0}, {'D',0} };
    vector<string> canned_inputs_49635 = {"a1 h1", "a2 h11", "a3 h10", "a4 h4", "h1 a4", "h4 h1", "c1 a3", "d1 h2", "d2 a2", "c2 h8", "c3 a1", "h8 h4", "c4 h6", "d3 c4", "d4 c3", "h6 d4", "h10 d3", "h11 d2", "b1 d1", "b2 c2", "b3 h8", "b4 c1", "h8 b4", "h4 b3", "h2 b2", "h1 b1"};
    vector<string> canned_inputs_49035 = {"a1 h1", "a2 h11", "a3 h10", "a4 h4", "h1 a4", "h4 h1", "c1 a3", "d1 h2", "d2 a2", "d3 h6", "d4 h8", "h10 d4", "h11 d3", "h8 h11", "h6 h10", "b1 d2", "c2 h8", "c3 a1", "h8 h4", "c4 d1", "h10 c4", "h11 c3", "b2 c2", "b3 h8", "b4 c1", "h8 b4", "h4 b3", "h2 b2", "h1 b1"};
    vector<string> manual_inputs = {}, canned_inputs = {};
    for (string canned_input : canned_inputs) {
        process_move(canned_input, burrow, moves);
        cout << endl << canned_input;
        output(burrow, moves);
    }
    string input;
    while (true) {
        output(burrow, moves);
        getline(cin, input);
        if (input == "exit") {
            for (const string& manual_input : manual_inputs) {
                cout << "\"" << manual_input << "\", ";
            }
            cout << endl << "Total cost " << (moves['A'] + 10*moves['B'] + 100*moves['C'] + 1000*moves['D']) << endl;
            exit(0);
        }
        if (process_move(input, burrow, moves)) {
            manual_inputs.push_back(input);
        }
    }
}