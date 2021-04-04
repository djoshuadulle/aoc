#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ARRAYINC 15


int parse_file(char* file_path, char* data[], int* cnt_ptr) {
    FILE* fp = fopen(file_path, "r");

    if (!fp) {
        return -1;
    }

    int array_size = ARRAYINC;
    char* data_tmp[array_size];
    int element_cnt = 0;

    while (element_cnt <= array_size) {
        // Set buffer and size to 0; they will be changed by getline.
        char* buffer = NULL;
        size_t size = 0;
        ssize_t chars = 1;

        // Read line.
        // The existing buffer will be re-used, or, if necessary.
        // It will be `free`'d and a new larger buffer will `malloc`'d.
        chars = getline(&buffer, &size, fp);

        // Discard newline character if it is present.
        if (chars > 0 && buffer[chars-1] == '\n') {
            buffer[chars-1] = '\0';
        } else {
            free(buffer);
            break;
        }

        data_tmp[element_cnt] = buffer;
        element_cnt++;

        if (element_cnt == array_size) {
            int new_size = array_size + ARRAYINC;

            char** temp = realloc(*data_tmp, sizeof(char*) * new_size);
            // If the function fails to allocate the requested block of memory,
            // a null pointer is returned, and the memory block
            // pointed to by argument ptr is not deallocated
            if (temp != NULL) {
                *data_tmp = temp;
                array_size = new_size;
            } else {
                return - 1;
            }
        }
    }

    *data = data_tmp;
    *cnt_ptr = element_cnt;
    return fclose(fp);
}


int fix_expense_report_two_val(char* data[], size_t kCnt) {
    int expense_vals[kCnt];

    for (size_t k = 0; k < kCnt; k++) {
        expense_vals[k] = atoi(data[k]);
    }

    for (size_t i = 0; i < kCnt - 2; i++) {
        for (size_t j = i+1; j < kCnt - 1; j++) {
            int val1 = expense_vals[i];
            int val2 = expense_vals[j];

            int sum = val1 + val2;

            if (sum == 2020) {
                return val1 * val2;
            }
        }
    }

    return -1;
}

int fix_expense_report_two_val(char* data[], size_t kCnt) {
    int expense_vals[kCnt];

    for (size_t l = 0; l < kCnt; l++) {
        expense_vals[l] = atoi(data[l]);
    }

    for (size_t i = 0; i < kCnt - 3; i++) {
        for (size_t j = i+1; j < kCnt - 2; j++) {
            for (size_t k = i+2; k < kCnt - 1; k++) {
                int val1 = expense_vals[i];
                int val2 = expense_vals[j];
                int val3 = expense_vals[k];

                int sum = val1 + val2 + val3;

                if (sum == 2020) {
                    return val1 * val2 * val3;
                }
            }
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        char* data[200];
        int cnt = 0;
        int* cnt_ptr = &cnt;

        if (parse_file(argv[1], data, cnt_ptr) != SUCCESS) {
            printf("Parse failed!\n");
        }

        printf("Successful parse.\n");

        int sol1 = fix_expense_report_two_val(data, cnt);
        printf("The corrected expense report value is: %d \n", sol1);

        int sol2 = fix_expense_report_three_val(data, cnt);
        printf("The corrected expense report value is: %d \n", sol2);
    }
}
