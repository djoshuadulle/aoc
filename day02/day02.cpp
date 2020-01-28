#include <fstream>
#include <iostream>
#include <vector>

inline int add(int val1, int val2);
inline int mult(int val1, int val2);


void intcode_it(std::vector<int> *vec, int *val_zero_idx) {
    std::vector<int> input = *vec;

    for (std::vector<int>::iterator it = input.begin(); it != input.end(); it++) {
        int opcode = *it;

        if (opcode == 99) {
            *val_zero_idx = input[0];
            return;
        }
        // kind of want to put an else here,
        // as a way of checking that I don't throw an index out of bounds error
        // or another type of error,
        // but maybe not needed since I know data is always good
        //

        int val1_addr = *(++it);
        int val2_addr = *(++it);
        int result_addr = *(++it);
        int result;

        if (opcode == 1) {
            result = add(input[val1_addr], input[val2_addr]);
        }

        if (opcode == 2) {
            result = mult(input[val1_addr], input[val2_addr]);
        }

        input[result_addr] = result;
    }
}

void intcode_i(std::vector<int> *vec, int *output) {
    std::vector<int> input = *vec;

    for (int ip = 0; ip < input.size(); ip+=4) {
        int opcode = input[ip];

        if (opcode == 99) {
            *output = input[0];
            return;
        }
        // kind of want to put an else here, with val1/val2/str_idx inside
        // as a way of checking that I don't throw an index out of bounds error
        // but maybe not needed since I know data is always good

        int val1_addr = input[ip + 1];  // param 1
        int val2_addr = input[ip + 2];  // param 2
        int result_addr = input[ip + 3];  // param 3
        int result;

        if (opcode == 1) {
            result = add(input[val1_addr], input[val2_addr]);
        }

        if (opcode == 2) {
            result = mult(input[val1_addr], input[val2_addr]);
        }

        input[result_addr] = result;
    }
}
void parseFileToVec(std::string input_path,
                    std::vector<int> *vec,
                    bool *success) {
    *success = false;
    std::ifstream input_file;
    input_file.open(input_path);
    if (input_file.is_open()) {
        std::string strVal;
        size_t sz;
        std::vector<int> tmpVec;

        while (getline(input_file, strVal, ',')) {
            int val = stoi(strVal, &sz);
            tmpVec.push_back(val);
        }
        *vec = std::move(tmpVec);
        *success = true;
    }
    return;
}

inline int add(int val1, int val2) {
    int result = val1 + val2;
    return result;
}

inline int mult(int val1, int val2) {
    int result = val1 * val2;
    return result;
}


void unit_test_one() {
    std::vector<int> input{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50};
    int program_output;
    intcode_i(&input, &program_output);
    std::cout << "Result in memory address zero is: " << program_output << std::endl;
    std::cout << "Result expected is: 3500" << std::endl;
}


void part_a_result() {
    std::string input_dir = "/Users/josh/repos/aoc-2019/day02/input.txt";

    std::vector<int> parsed_input;
    bool success = false;
    parseFileToVec(input_dir, &parsed_input, &success);

    if (success) {
        std::cout << "File parsed." << std::endl;
        int program_output;
        intcode_i(&parsed_input, &program_output);
        std::cout << "Result in memory address zero is: " << program_output << std::endl;
    } else {
        std::cout << "Error parsing file." <<std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Running..." << std::endl;
    unit_test_one();
    part_a_result();
}
