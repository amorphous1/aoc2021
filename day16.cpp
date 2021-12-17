#include <vector>
#include <string>
#include <map>

using namespace std;

struct Packet {
    int version;
    string type;
    vector<Packet> children;
    unsigned long value;
    int length;

    int version_sum() {
        int result = version;
        for (Packet child : children) {
            result += child.version_sum();
        }
        return result;
    }

    string repr() {
        string result = " { v" + to_string(version) + " " + type + " = " + to_string(value) + " #" + to_string(length) + " [";
        for (Packet child : children) {
            result += child.repr();
        }
        result += "] } ";
        return result;
    }
};

Packet parse_packet(const string& packet, int start) {
    int version = stoi(packet.substr(start, 3), nullptr, 2);
    int type_id = stoi(packet.substr(start + 3, 3), nullptr, 2);
    int pos = start + 6;
    cout << "version " << version << " type_id " << type_id << endl;
    if (type_id == 4) { // literal value
        string value;
        do {
            cout << "  " << packet << " " << pos << " " << value << endl;
            value += packet.substr(pos + 1, 4);
            pos += 5;
        } while (packet.at(pos - 5) == '1');
        return { version, "literal", {}, stoul(value, nullptr, 2), pos - start };
    }
    // operator packet
    vector<Packet> children;
    if (packet.at(pos) == '0') { // 15 bit representing total size of children in bits
        int end_pos = pos + 1 + 15 + stoi(packet.substr(pos + 1, 15), nullptr, 2);
        pos += 1 + 15;
        while (pos < end_pos) {
            Packet child = parse_packet(packet, pos);
            pos += child.length;
            children.push_back(child);
        }
    } else { // 11 bit representing number of children
        int num_children = stoi(packet.substr(pos + 1, 11), nullptr, 2);
        pos += 1 + 11;
        for (int i = 1; i <= num_children; i++) {
            Packet child = parse_packet(packet, pos);
            pos += child.length;
            children.push_back(child);
        }
    }
    return { version, "operator", children, 0, pos - start };
}

unsigned long day16a(const string& hex_input) {
    map<char, string> hex_to_bin = {
            { '0', "0000" }, { '1', "0001" }, { '2', "0010" }, { '3', "0011" },
            { '4', "0100" }, { '5', "0101" }, { '6', "0110" }, { '7', "0111" },
            { '8', "1000" }, { '9', "1001" }, { 'A', "1010" }, { 'B', "1011" },
            { 'C', "1100" }, { 'D', "1101" }, { 'E', "1110" }, { 'F', "1111" },
    };
    string packet_text;
    for (char ch : hex_input) {
        packet_text += hex_to_bin.at(ch);
    }
    Packet packet = parse_packet(packet_text, 0);
    cout << packet.repr() << endl;
    return packet.version_sum();
}
