#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

namespace std {


float calculateFuelReqA(string input_dir, bool part_b);
float calculateFuelReqB(float module_fuel_req);


float calculateFuelReqA(string input_dir, bool part_b) {
    if (input_dir.empty()) {return -1; }

    float fuel_total = 0;

    ifstream input_file;
    input_file.open(input_dir);
    if (input_file.is_open()) {
        string module;
        size_t sz;
        while (getline(input_file, module)) {
            float module_fuel_req = floor(stof(module, &sz)/3.0) - 2;
            if (part_b) {
                float added_fuel_req = calculateFuelReqB(module_fuel_req);
                fuel_total += (module_fuel_req + added_fuel_req);
            } else {
                fuel_total += module_fuel_req;
            }
        }
        return fuel_total;
    } else {
        return -1;
    }
}

float calculateFuelReqB(float module_fuel_req) {
    float total_added_fuel;
    float added_fuel_req = floor(module_fuel_req/3.0) - 2;
    while (added_fuel_req > 0) {
        total_added_fuel += added_fuel_req;
        added_fuel_req = floor(added_fuel_req/3.0) - 2;
    }
    return total_added_fuel;
}

}  // namespace std

int main() {
    std::string input_dir;
    std::cout << "Please enter full path to input file." << std::endl;
    getline(std::cin, input_dir);

    int fuel_req_a = calculateFuelReqA(input_dir, false);
    if (fuel_req_a < 0) {
        std::cout << "Error opening the input data." << std::endl;
    } else {
        std::cout << "The total fuel requirement for part A is: "
        << fuel_req_a << std::endl;
    }

    int fuel_req_b = calculateFuelReqA(input_dir, true);
    if (fuel_req_b < 0) {
        std::cout << "Error opening the input data." << std::endl;
    } else {
        std::cout << "The total fuel requirement for part B is: "
        << fuel_req_b << std::endl;
    }
}
