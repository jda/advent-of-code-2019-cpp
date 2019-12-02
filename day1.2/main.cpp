#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

int findfuel(int mass) {
    std::cout << "Mass: " << mass << std::endl;
    float stage1 = mass / (1.0 * 3);
    std::cout << "\tstage1: " << stage1 << std::endl;
    int stage2 = floor(stage1);
    std::cout << "\tstage2: " << stage2 << std::endl;
    int stage3 = stage2 - 2;
    std::cout << "\tstage3: " << stage3 << std::endl;


    return stage3;
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

    int fuelreq = 0;
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

        std::string rawPartMass (line.substr(0));
        // fuel to haul mass
        int partFuel = std::stoll(rawPartMass);
        int payloadFuel = findfuel(partFuel);
        fuelreq += payloadFuel;

        int supportFuel = findfuel(payloadFuel);
        while (supportFuel > 0) {
            fuelreq += supportFuel;
            supportFuel = findfuel(supportFuel);
        }


    }
    infile.close();

    std::cout << "Fuel required: " << fuelreq << std::endl;
}