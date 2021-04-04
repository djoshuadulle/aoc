#include <assert.h>
#include <iostream>
#include <string>


int validate_candidate_A(std::string candidate) {
    bool adjacent_pair = false;

    for (int i = 0; i < candidate.length() - 1; i++) {
        const char& val_a = candidate.at(i);
        const char& val_b = candidate.at(i+1);

        if (val_a > val_b) {
            return 0;
        }

        if (val_a == val_b) {
            adjacent_pair = true;
        }
    }

    return static_cast<int>(adjacent_pair);
}

int validate_candidate_B(std::string candidate) {
    bool adjacent_pair = false;
    char first_pair = '\0';
    char pair_val = '\0';

    for (int i = 0; i < candidate.length() - 1; i++) {
        const char& val_a = candidate.at(i);
        const char& val_b = candidate.at(i+1);

        if (val_a > val_b) {
            return 0;
        }

        if (val_a != val_b) {
            continue;
        }

        if (val_b == pair_val) {
            if (first_pair == pair_val) {
                adjacent_pair = false;
                first_pair = '\0';
            }
            continue;
        }

        if (first_pair == '\0') {
            adjacent_pair = true;
            first_pair = val_b;
            pair_val = val_b;
            continue;
        }

        pair_val = val_b;
    }

    return static_cast<int>(adjacent_pair);
}

int count_candidates_in_range_A(int start, int end) {
    int count = 0;
    int candidate = start;

    while (candidate <= end) {
        std::string candidate_str = std::to_string(candidate);

        count += validate_candidate_A(candidate_str);
        candidate++;
    }

    return count;
}

int count_candidates_in_range_B(int start, int end) {
    int count = 0;
    int candidate = start;

    while (candidate <= end) {
        std::string candidate_str = std::to_string(candidate);

        count += validate_candidate_B(candidate_str);
        candidate++;
    }

    return count;
}

void testCaseA() {
    std::string testA = "111111";  // pass
    std::string testB = "223450";  // fail; decrease
    std::string testC = "123789";  // fail; no double

    int pass = 0;

    pass = validate_candidate_A(testA);
    assert(pass == 1);

    pass = validate_candidate_A(testB);
    assert(pass == 0);

    pass = validate_candidate_A(testC);
    assert(pass == 0);
}

void testCaseB() {
    std::string testA = "112233";  // pass
    std::string testB = "123444";  // fail
    std::string testC = "111122";  // pass
    std::string testD = "555779";  // pass
    std::string testE = "223335";  // pass
    std::string testF = "145899";  // pass


    int pass = 0;

    pass = validate_candidate_B(testA);
    assert(pass == 1);

    pass = validate_candidate_B(testB);
    assert(pass == 0);

    pass = validate_candidate_B(testC);
    assert(pass == 1);

    pass = validate_candidate_B(testD);
    assert(pass == 1);

    pass = validate_candidate_B(testE);
    assert(pass == 1);

    pass = validate_candidate_B(testF);
    assert(pass == 1);
}

void partA() {
    // data give in puzzle
    int start = 172930;
    int end = 683082;

    int solA = count_candidates_in_range_A(start, end);
    printf("solA: %d\n", solA);
}

void partB() {
    // data give in puzzle
    int start = 172930;
    int end = 683082;

    int solB = count_candidates_in_range_B(start, end);
    printf("solB: %d\n", solB);
}


int main(int argc, char* argv[]) {
    testCaseA();
    testCaseB();
    partA();
    partB();
}
