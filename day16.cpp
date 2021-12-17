#include <vector>
#include <string>
#include <map>
#include <climits>

using namespace std;

struct Packet {
    int version;
    string type;
    vector<Packet> children;
    unsigned long value;

    int version_sum() {
        int result = version;
        for (Packet child : children) {
            result += child.version_sum();
        }
        return result;
    }
};

Packet parse_packet(const string& packet, int& pos) {
    const map<int, string> bits_operators = { {0, "sum"}, {1, "product"}, {2, "min"}, {3, "max"}, {4, "val"}, {5, "gt"}, {6, "lt"}, {7, "eq"}, };
    const int version = stoi(packet.substr(pos, 3), nullptr, 2);
    const string type = bits_operators.at(stoi(packet.substr(pos + 3, 3), nullptr, 2));
    pos += 6;
    if (type == "val") { // literal value
        string value;
        do {
            value += packet.substr(pos + 1, 4);
            pos += 5;
        } while (packet.at(pos - 5) == '1');
        return { version, type, {}, stoul(value, nullptr, 2) };
    }
    vector<Packet> children;
    if (packet.at(pos) == '0') { // 15 bit representing total size of children in bits
        const int end_pos = pos + 1 + 15 + stoi(packet.substr(pos + 1, 15), nullptr, 2);
        pos += 1 + 15;
        while (pos < end_pos) {
            children.push_back(parse_packet(packet, pos));
        }
    } else { // 11 bit representing number of children
        const int num_children = stoi(packet.substr(pos + 1, 11), nullptr, 2);
        pos += 1 + 11;
        for (int i = 1; i <= num_children; i++) {
            children.push_back(parse_packet(packet, pos));
        }
    }
    unsigned long value = 0;
    if (type == "sum") {
        for (const Packet& child : children) {
            value += child.value;
        }
    } else if (type == "product") {
        value = 1;
        for (const Packet& child : children) {
            value *= child.value;
        }
    } else if (type == "min") {
        value = ULONG_MAX;
        for (const Packet& child : children) {
            value = min(value, child.value);
        }
    } else if (type == "max") {
        for (const Packet& child : children) {
            value = max(value, child.value);
        }
    } else if (type == "gt") {
        value = children.at(0).value > children.at(1).value ? 1 : 0;
    } else if (type == "lt") {
        value = children.at(0).value < children.at(1).value ? 1 : 0;
    } else if (type == "eq") {
        value = children.at(0).value == children.at(1).value ? 1 : 0;
    } else {
        throw invalid_argument("unknown operator type " + type);
    }
    return { version, type, children, value };
}

string convert_to_binary(const string &hex_input) {
    const map<char, string> hex_to_bin = {
            { '0', "0000" }, { '1', "0001" }, { '2', "0010" }, { '3', "0011" },
            { '4', "0100" }, { '5', "0101" }, { '6', "0110" }, { '7', "0111" },
            { '8', "1000" }, { '9', "1001" }, { 'A', "1010" }, { 'B', "1011" },
            { 'C', "1100" }, { 'D', "1101" }, { 'E', "1110" }, { 'F', "1111" },
    };
    string packet_text;
    for (char ch : hex_input) {
        packet_text += hex_to_bin.at(ch);
    }
    return packet_text;
}

unsigned long day16a(const string& hex_input) {
    int start_pos = 0;
    Packet packet = parse_packet(convert_to_binary(hex_input), start_pos);
    return packet.version_sum();
}

unsigned long day16b(const string& hex_input) {
    int start_pos = 0;
    Packet packet = parse_packet(convert_to_binary(hex_input), start_pos);
    return packet.value;
}
