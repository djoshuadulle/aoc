#include <fstream>
#include <iostream>
#include <vector>


enum {
    HALT = 99,
    ADD = 1,
    MULT = 2,
};

inline int add(int val1, int val2) {
    int result = val1 + val2;
    return result;
}

inline int mult(int val1, int val2) {
    int result = val1 * val2;
    return result;
}

void intcode_it(std::vector<int>& memory, int& output) {
    std::vector<int> input = memory;

    for (std::vector<int>::iterator it = input.begin();
        it != input.end(); it++) {
        int opcode = *it;

        if (opcode == HALT) {
            output = input[0];
            return;
        }

        int val1_addr = *(++it);  // param1
        int val2_addr = *(++it);  // param2
        int result_addr = *(++it);  // param3
        int result;

        if (opcode == ADD) {
            result = add(input[val1_addr], input[val2_addr]);
        }

        if (opcode == MULT) {
            result = mult(input[val1_addr], input[val2_addr]);
        }

        input[result_addr] = result;
    }
}

// this function does same as above w/o iterators.
void intcode_i(std::vector<int>& memory, int& output) {
    std::vector<int> input = memory;

    for (unsigned ip = 0; ip < input.size(); ip += 4) {
        int opcode = input[ip];

        if (opcode == HALT) {
            output = input[0];
            return;
        }

        int val1_addr = input[ip + 1];  // param 1
        int val2_addr = input[ip + 2];  // param 2
        int result_addr = input[ip + 3];  // param 3
        int result;

        if (opcode == ADD) {
            result = add(input[val1_addr], input[val2_addr]);
        }

        if (opcode == MULT) {
            result = mult(input[val1_addr], input[val2_addr]);
        }

        input[result_addr] = result;
    }
}

void output_finder(std::vector<int>* memory,
                   std::pair<int, int>* result,
                   bool* success) {
    const int kGoalResult = 19690720;

    for (int noun = 0; noun <= 99 ; noun++) {
        for (int verb = 0; verb <= 99 ; verb++) {
            std::vector<int> memory_local(*memory);
            memory_local[1] = noun;
            memory_local[2] = verb;

            int program_output;
            intcode_i(memory_local, program_output);

            if (program_output == kGoalResult) {
                *result = std::make_pair(noun, verb);
                *success = true;
                return;
            }
        }
    }
}

void parseFileToMemory(std::string input_path,
                    std::vector<int>* memory,
                    bool* success) {
    *success = false;
    std::ifstream input_file;
    input_file.open(input_path);
    if (input_file.is_open()) {
        std::string strVal;
        std::vector<int> memory_local;

        while (getline(input_file, strVal, ',')) {
            int val = stoi(strVal, nullptr);
            memory_local.push_back(val);
        }
        *memory = std::move(memory_local);
        *success = true;
    }
}

void unit_test_one() {
    std::vector<int> input{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50};
    int program_output;
    intcode_i(input, program_output);
    std::cout << "Result in memory address zero is: " << program_output << std::endl;
    std::cout << "Result expected is: 3500" << std::endl;
}


void calc_part_a_result() {
    std::cout << "Part A" << std::endl;
    // std::string input_dir = "/Users/josh/repos/aoc-2019/day02/input.txt";  //work linux
    std::string input_dir = "/home/jdulle/jrepos/aoc-2019/day02/input.txt";  // personal mac

    std::vector<int> parsed_input;
    bool success = false;
    parseFileToMemory(input_dir, &parsed_input, &success);

    if (!success) {
        std::cout << "Error parsing file." <<std::endl;
        return;
    }
    std::cout << "File parsed." << std::endl;

    int program_output;
    intcode_i(parsed_input, program_output);
    std::cout << "Result in memory address zero is: " << program_output << std::endl;
}

void calc_part_b_result() {
    std::cout << "Part B" << std::endl;
    // std::string input_dir = "/Users/josh/repos/aoc-2019/day02/input.txt";  //work linux
    std::string input_dir = "/home/jdulle/jrepos/aoc-2019/day02/input.txt";  // personal mac

    std::vector<int> parsed_input;
    bool success = false;
    parseFileToMemory(input_dir, &parsed_input, &success);

    if (!success) {
        std::cout << "Error parsing file." <<std::endl;
        return;
    }
    std::cout << "File parsed." << std::endl;

    std::pair<int, int> result;
    bool pair_found = false;
    output_finder(&parsed_input, &result, &pair_found);

    if (!pair_found) {
        std::cout << "No result pair found." <<std::endl;
        return;
    }

    int noun = result.first;
    int verb = result.second;
    int aoc_soln = 100 * noun + verb;
    std::cout << "The noun is: " << noun << std::endl;
    std::cout << "The verb is: " << verb << std::endl;
    std::cout << "The final solution is: " << aoc_soln << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "Running..." << std::endl;
    unit_test_one();
    calc_part_a_result();
    calc_part_b_result();
}
