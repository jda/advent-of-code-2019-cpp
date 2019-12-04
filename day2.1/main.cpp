#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <iterator>

#include <boost/algorithm/string.hpp>


std::vector<int> intcode(std::vector<int> intcode) {
    for(std::vector<int>::size_type i = 0; i != intcode.size(); i = i + 4) {
        int addrIn1 = 0;
        int addrIn2 = 0;
        int addrOut = 0;
        switch (intcode[i]) {
            case 1:
                addrIn1 = intcode[i+1];
                addrIn2 = intcode[i+2];
                addrOut = intcode[i+3];
                intcode[addrOut] = intcode[addrIn1] + intcode[addrIn2];
                break;
            case 2:
                addrIn1 = intcode[i+1];
                addrIn2 = intcode[i+2];
                addrOut = intcode[i+3];
                intcode[addrOut] = intcode[addrIn1] * intcode[addrIn2];
                break;
            case 99:
                return intcode;
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

        // process intcode
        auto processed = intcode(code);

        std::cout << "program output:\n\t";
        for(auto it = std::begin(processed); it != std::end(processed); it++) {
            std::cout << *it;
            if ( it+1 != std::end(processed)) {
                std::cout << ",";
            }
        }   
        std::cout << std::endl << std::endl;
    }
    infile.close();

}