#include <iostream>
#include <variant>

#include "../utils/library.h"

using namespace Cast;

struct Packet;

using PacketData = std::variant<int, Packet>;

enum class Result  {
    RIGHT = -1,
    EQUAL,
    LEFT,

};

auto packetOrder(const Packet& left, const Packet& right) -> Result;

struct Packet {
    std::list<PacketData> content;

    auto print() const -> void {
        std::cout << "[";
        for (auto e = content.begin(); e != content.end(); e++) {
            if (holds_alternative<int>(*e)) {
                std::cout << get<int>(*e);
                if (std::next(e) != content.end())
                    std::cout << ", ";
            } else {
                get<Packet>(*e).print();
            }
        }
        std::cout << "], ";
    }

    bool operator<(const Packet& b) const {
        return packetOrder(*this, b) == Result::LEFT;
    }

    bool operator==(const Packet& b) const {
        return packetOrder(*this, b) == Result::EQUAL;
    }
};

struct PacketPair {
    Packet left, right;
};

auto bothInts(const PacketData& a, const PacketData& b) -> bool {
    return holds_alternative<int>(a) && holds_alternative<int>(b);
}

auto bothPackets(const PacketData& a, const PacketData& b) -> bool {
    return holds_alternative<Packet>(a) && holds_alternative<Packet>(b);
}

auto packetOrder(const Packet& left, const Packet& right) -> Result {
    auto l = left.content.begin();
    auto r = right.content.begin();

    for (; l != left.content.end() && r != right.content.end(); l++, r++) {
        if (bothInts(*l, *r)) {
            if (get<int>(*l) == get<int>(*r)) continue;

            return get<int>(*l) < get<int>(*r) ? Result::LEFT : Result::RIGHT;
        }

        else if (bothPackets(*l, *r)) {
            auto res = packetOrder(get<Packet>(*l), get<Packet>(*r));
            if (res != Result::EQUAL)
                return res;
        }

        else {
            Packet p;
            auto val = std::holds_alternative<int>(*l) ? get<int>(*l) : get<int>(*r);

            p.content.emplace_back(val);


            if (std::holds_alternative<int>(*l)) {
                auto res = packetOrder(p, get<Packet>(*r));
                if (res != Result::EQUAL)
                    return res;
            } else {
                auto res = packetOrder(get<Packet>(*l), p);
                if (res != Result::EQUAL)
                    return res;
            }
        }
    }

    if (left.content.size() != right.content.size()) {
        return l == left.content.end() ? Result::LEFT : Result::RIGHT;
    }

    return Result::EQUAL;
}


auto strToPacket(const std::string& str)-> Packet {
    Packet newPacket;

    int value = -1, size = 1;

    // Don't iterate over beginning [ and end ]
    for (int c = str.size()-2; c >= 0; c--) {
        if ((str[c] == ',' || c == 0) && value != -1) {
            newPacket.content.emplace_front(value);
            value = -1;
            size = 1;
            continue;
        }

        if (str[c] == ' ')
            continue;

        int e = c-1;
        if (str[c] == ']') {
            int brackets = 1;
            for (; e > 0; e--) {
                if (str[e] == ']')
                    brackets++;
                else if (str[e] == '[')
                    brackets--;

                if (brackets == 0)
                    break;
            }
            newPacket.content.emplace_front(strToPacket(str.substr(e, c-e+1)));
            c = e-1;
        } else if (isdigit(str[c])) {
            value = value == -1 ? (cto<int>(str[c]) * size) : value + (cto<int>(str[c]) * size);
            size *= 10;
        }
    }

    return newPacket;
}

auto printPackets(const std::vector<PacketPair>& packets) {
    for (auto& elem : packets) {
        elem.left.print();
        std::cout << "\n";
        elem.right.print();
        std::cout << "\n\n";
    }
}

auto readInput(const std::string& filePath) {
    std::vector<PacketPair> packets;

    std::fstream file(filePath);

    if (file.is_open()) {
        std::string line;
        PacketPair pp;

        bool first = true;
        while (getline(file, line)) {
            if (line.empty()) {
                packets.emplace_back(pp);
                continue;
            }

            if (first) {
                pp.left = strToPacket(line);
            } else {
                pp.right = strToPacket(line);
            }

            first = !first;
        }
    }

    return packets;
}

int main() {
    auto packets = readInput("input.txt");

    std::cout << packets.size() << std::endl;

    int sum = 0;
    for (int i = 0; i < packets.size(); i++) {
        if (packetOrder(packets[i].left, packets[i].right) == Result::LEFT) {
            sum += i+1;
        }
    }

    std::cout << "Total: " << sum << std::endl;

    // Part 2 : Sort packets
    Packet divider1 = strToPacket("[[2]]"), divider2 = strToPacket("[[6]]");

    std::vector<Packet> individualPackets;
    for (auto& elem : packets) {
        individualPackets.push_back(elem.left);
        individualPackets.push_back(elem.right);
    }

    individualPackets.push_back(divider1);
    individualPackets.push_back(divider2);

    std::sort(individualPackets.begin(), individualPackets.end(), [](const Packet& a, const Packet& b) {
        return packetOrder(a, b) == Result::LEFT;
    });

    int index1 = -1, index2 = -1;

    for (int i = 0; i < individualPackets.size(); ++i) {
        if (individualPackets[i] == divider1)
            index1 = i + 1;

        else if (individualPackets[i] == divider2)
            index2 = i + 1;

        if (index1 != -1 && index2 != -1)
            break;
    }

    std::cout << "[[2]] : " << index1 << ",  [[6]] : " << index2 << std::endl;
    std::cout << "Decoder value: " << index1 * index2 << std::endl;


    return 0;
}
