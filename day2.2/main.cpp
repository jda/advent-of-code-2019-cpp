#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <iterator>

#include <boost/algorithm/string.hpp>


std::vector<int> mutateIntcode(std::vector<int> intcode, int noun, int verb) {
    std::vector<int> newcode = intcode;
    newcode[1] = noun;
    newcode[2] = verb;
    return newcode;
}

std::vector<int> intcode(std::vector<int> intcode) {
    for(std::vector<int>::size_type i = 0; i != intcode.size(); i = i + 4) {
        if (intcode[i] == 99) {
            return intcode;
        }

        int addrIn1 = intcode[i+1];
        int addrIn2 = intcode[i+2];
        int addrOut = intcode[i+3];
        switch (intcode[i]) {
            case 1:
                intcode[addrOut] = intcode[addrIn1] + intcode[addrIn2];
                break;
            case 2:
                intcode[addrOut] = intcode[addrIn1] * intcode[addrIn2];
                break;
        }
    }

    return intcode;
}

std::vector<int> strToIntVec(std::string input) {
    std::vector<int> intcode;

    std::vector<std::string> chunks;
    boost::split(chunks, input, boost::is_any_of(","));
    for (auto & chunk : chunks) {
        int code = std::stoi(chunk);
        intcode.push_back(code);
    }
    
    return intcode;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <FILE>" << std::endl;
        return 1;
    }

    std::string infileName = argv[1];

    std::ifstream infile;
    infile.open(infileName);
    if (!infile.is_open()) {
        std::cerr << "Could not open file " << infileName << std::endl;
        return 1;
    }

    std::string line;
    
    while (std::getline(infile, line)) {
        // skip blank
        if (line.empty()) {
            continue;
        }

        // skip commented
        if (line.rfind("#") == 0) {
            continue;
        }

        // to array
        std::cout << "program input:\n\t" << line << std::endl;
        auto code = strToIntVec(line);
        infile.close();

        // process intcode
        int min = 0;
        int max = 99;
        int check = 19690720;

        for (int x = min; x != max; x++) {
            for (int y = min; y != max; y++) {
                auto mutated = mutateIntcode(code, x, y);
                auto processed = intcode(mutated);

                if (processed[0] == check) {
                    std::cout << "Found " << check << " with noun " << x << " and verb " << y << std::endl;
                    return 0;
                }
            }
        }
    }
}

/*
noun = intcode[1]
verb = intcode[2]

Find the input noun and verb that cause the program to produce the output 19690720. What is 100 * noun + verb? (For example, if noun=12 and verb=2, the answer would be 1202.)
since both are memory addresses, search space is limited to (len(intcode) / 4) +1
*/