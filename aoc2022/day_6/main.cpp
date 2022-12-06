#include <iostream>

#include "../utils/library.h"


auto findEndOfUniqueString(const std::string& signal, int start, int packetSize)  {
    if (signal.size() - start - 1 < packetSize)
        return std::tuple(-1, false);

    for (int offset = 0; offset < packetSize-1; offset++) {
        for (int succeedingLetters = offset + 1; succeedingLetters < packetSize; succeedingLetters++) {
            if (signal[start+offset] == signal[start+succeedingLetters])
                return std::tuple(start + offset + 1, false);
        }
    }

    return std::tuple(start + packetSize-1, true);
}

int main() {
    auto signalString = readInputToStringVector("input.txt")[0];

    int endOfPackage = 0;
    
    
    // Find start of packet which has a size of 4
    for (bool found = false; endOfPackage < signalString.size() && !found; ) {
        std::tie(endOfPackage, found) = findEndOfUniqueString(signalString, endOfPackage, 4);
    }

    int endOfMessage = 0;

    // Find start of message which has a size of 14
    for (bool found = false; endOfMessage < signalString.size() && !found; ) {
        std::tie(endOfMessage, found) = findEndOfUniqueString(signalString, endOfMessage, 14);
    }

    std::cout << "Number of letters needed to process to find start of packet: " << endOfPackage + 1 << std::endl;
    std::cout << "Number of letters needed to process to find start of message: " << endOfMessage + 1 << std::endl;

    return 0;
}
