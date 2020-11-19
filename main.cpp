
#include "Simulation.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cout << "Error: Incorrect number of command line arguments provided" << endl;
        return 1;
    }

    Simulation sim(argv[1]);


    return 0;
}