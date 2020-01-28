#include <fstream>
#include <iostream>
#include <vector>

inline int add(int val1, int val2);
inline int mult(int val1, int val2);


void intcode_it(std::vector<int> *vec, int *val_zero_idx) {
    std::vector<int> input = *vec;

    for (std::vector<int>::iterator it = input.begin(); it != input.end(); it++) {
        int op_code = *it;

        if (op_code == 99) {
            *val_zero_idx = input[0];
            return;
        }
        // kind of want to put an else here, with val1/val2/str_idx inside
        // as a way of checking that I don't throw an index out of bounds error
        // but maybe not needed since I know data is always good

        int pos_val1 = *(++it);
        int pos_val2 = *(++it);
        int store_idx = *(++it);
        int result;

        if (op_code == 1) {
            result = add(input[pos_val1], input[pos_val2]);
        }

        if (op_code == 2) {
            result = mult(input[pos_val1], input[pos_val2]);
        }

        input[store_idx] = result;
    }
}

void intcode_i(std::vector<int> *vec, int *val_zero_idx) {
    std::vector<int> input = *vec;

    for (int i = 0; i < input.size(); i+=4) {
        int op_code = input[i];

        if (op_code == 99) {
            *val_zero_idx = input[0];
            return;
        }
        // kind of want to put an else here, with val1/val2/str_idx inside
        // as a way of checking that I don't throw an index out of bounds error
        // but maybe not needed since I know data is always good

        int pos_val1 = input[i + 1];
        int pos_val2 = input[i + 2];
        int store_idx = input[i + 3];
        int result;

        if (op_code == 1) {
            result = add(input[pos_val1], input[pos_val2]);
        }

        if (op_code == 2) {
            result = mult(input[pos_val1], input[pos_val2]);
        }

        input[store_idx] = result;
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
    std::vector<int> parsed_input{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50};
    int val_zero_pos;
    intcode_i(&parsed_input, &val_zero_pos);
    std::cout << "Result in index zero is: " << val_zero_pos << std::endl;
    std::cout << "Result expected is: 3500" << std::endl;
}


void part_a_result() {
    std::string input_dir = "/Users/josh/repos/aoc-2019/day02/input.txt";

    std::vector<int> parsed_input;
    bool success = false;
    parseFileToVec(input_dir, &parsed_input, &success);

    if (success) {
        std::cout << "File parsed." << std::endl;
        int pos_zero_after;
        intcode_it(&parsed_input, &pos_zero_after);
        std::cout << "Result in index zero is: " << pos_zero_after << std::endl;
    } else {
        std::cout << "Error parsing file." <<std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Running..." << std::endl;
    unit_test_one();
    part_a_result();
}
