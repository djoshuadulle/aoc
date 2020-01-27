#include <fstream>
#include <iostream>
#include <vector>



inline int add(int val1, int val2);
inline int mult(int val1, int val2);


void parseFileToVec(std::string input_path,
                    std::vector<int> *vec, bool *success) {
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


int main(int argc, char* argv[]) {
    std::string input_dir = "/home/jdulle/jrepos/aoc-2019/day02/input.txt";

    std::vector<int> vec;
    bool success = false;
    parseFileToVec(input_dir, &vec, &success);

    if (success) {
        std::cout << "yay" << std::endl;
    } else {
        std::cout << "boo" << std::endl;
    }
}
