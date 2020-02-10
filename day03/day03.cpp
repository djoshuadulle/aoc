
#include <assert.h>
#include <climits>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// INTERSECTION FINDING FUNCTIONS
const std::pair<int, int> CENTRAL_PORT(0, 0);

const std::pair<int, int> get_start_point() {
    return CENTRAL_PORT;
}

std::pair<int, int> get_last_step(const std::set<std::pair<int, int>>& segment,
                                   const char& direction) {
    bool positive_move = (direction == 'R' || direction == 'U');
    bool negative_move = (direction == 'L' || direction == 'D');
    std::pair<int, int> last_point;

    if (positive_move) {
    // Because sets order from smallest to biggest, e.g. -10, ..., 0, ..., 10
    // positive moves from (0, 0) result in last element being the end point
        std::set<std::pair<int, int>>::reverse_iterator end_pt;
        end_pt = segment.rbegin();
        last_point = *end_pt;
    }

    if (negative_move) {
    // Because sets order from smallest to biggest, e.g. -10, ..., 0, ..., 10
    // negative moves from (0, 0) result in first element being the end point
        std::set<std::pair<int, int>>::iterator beg_pt;
        beg_pt = segment.begin();
        last_point = *beg_pt;
    }
    return last_point;
}

std::pair<int, int> right(const std::pair<int, int>& curr_point) {
    std::pair<int, int> next_point;
    next_point.first = curr_point.first + 1;
    next_point.second = curr_point.second;

    return next_point;
}

std::pair<int, int> left(const std::pair<int, int>& curr_point) {
    std::pair<int, int> next_point;
    next_point.first = curr_point.first - 1;
    next_point.second = curr_point.second;

    return next_point;
}

std::pair<int, int> up(const std::pair<int, int>& curr_point) {
    std::pair<int, int> next_point;
    next_point.first = curr_point.first;
    next_point.second = curr_point.second + 1;

    return next_point;
}

std::pair<int, int> down(const std::pair<int, int>& curr_point) {
    std::pair<int, int> next_point;
    next_point.first = curr_point.first;
    next_point.second = curr_point.second - 1;

    return next_point;
}

int get_manhattan_distance(const std::pair<int, int>& pointA,
                           const std::pair<int, int>& pointB) {
    int x_distance = abs(pointB.first - pointA.first);
    int y_distance = abs(pointB.second - pointA.second);
    int manhattanDistance = x_distance + y_distance;

    return manhattanDistance;
}

// Q: Is there a convention for chars as 'n' vs "n"?
std::set<std::pair<int, int>> map_wire_segment(const std::pair<int, int>& start_point,
                                               const char& direction,
                                               const int& steps) {
    std::pair<int, int> curr_point = start_point;
    std::pair<int, int> next_point;

    std::set<std::pair<int, int>> segment;

    for (int i = 0; i < steps; i++) {
        if (direction == 'R') {
            next_point = right(curr_point);
        }
        if (direction == 'L') {
            next_point = left(curr_point);
        }
        if (direction == 'U') {
            next_point = up(curr_point);
        }
        if (direction == 'D') {
            next_point = down(curr_point);
        }
        segment.insert(next_point);
        curr_point = next_point;
    }
    return segment;
}

// Q: I was getting some weirdness w/ the iterator when the input was a const.
//error: passing ‘const iterator {aka const __gnu_cxx::__normal_iterator<std::pair<char, int>*,
//std::vector<std::pair<char, int> > >}’ as ‘this’ argument discards qualifiers [-fpermissive]
std::set<std::pair<int, int>> map_wire_path(std::vector<std::pair<char, int>>& wire_path) {
    std::set<std::pair<int, int>> full_path;

    std::pair<int, int> curr_point = get_start_point();
    char direction;
    int steps;

    std::vector<std::pair<char, int>>::iterator it;
    for (it = wire_path.begin(); it != wire_path.end(); it++) {
        direction = it->first;
        steps = it->second;

        std::set<std::pair<int, int>> segment;
        segment = map_wire_segment(curr_point, direction, steps);

        curr_point = get_last_step(segment, direction);
        full_path.insert(segment.begin(), segment.end());
    }
    return full_path;
}

// Q: If const'ing above, that error trickles down to here when these are
// passed as const.
// error: binding reference of type ‘std::vector<std::pair<char, int> >&’ to
// ‘const std::vector<std::pair<char, int> >’ discards qualifiers
//     full_path_A = map_wire_path(wire_path_A);
int find_closest_intersection(std::vector<std::pair<char, int>>& wire_path_A,
                              std::vector<std::pair<char, int>>& wire_path_B) {
    std::set<std::pair<int, int>> full_path_A;
    full_path_A = map_wire_path(wire_path_A);

    std::set<std::pair<int, int>> full_path_B;
    full_path_B = map_wire_path(wire_path_B);

    int manhattanDistance = INT_MAX;
    for (auto const &pt : full_path_A) {
        int distance = INT_MAX;

        // Seaches path B for points in path A
        auto intrsct_ptr = full_path_B.find(pt);
        bool intersection_found = (intrsct_ptr != full_path_B.end());
        if (intersection_found) {
            distance = get_manhattan_distance(CENTRAL_PORT, *intrsct_ptr);
        }

        bool nearest = (distance < manhattanDistance);
        if (nearest) {
            manhattanDistance = distance;
        }
    }
    return manhattanDistance;
}

std::vector<std::pair<int, int>> find_intersections(
                            std::vector<std::pair<char, int>>& wire_path_A,
                            std::vector<std::pair<char, int>>& wire_path_B) {
    std::set<std::pair<int, int>> full_path_A;
    full_path_A = map_wire_path(wire_path_A);

    std::set<std::pair<int, int>> full_path_B;
    full_path_B = map_wire_path(wire_path_B);

    std::vector<std::pair<int, int>> intersection_list;
    for (auto const &pt : full_path_A) {
        // Seaches path B for points in path A
        auto intrsct_ptr = full_path_B.find(pt);
        bool intersection_found = (intrsct_ptr != full_path_B.end());
        if (intersection_found) {
            intersection_list.push_back(*intrsct_ptr);
        }
    }
    return intersection_list;
}

int calculate_total_steps(std::pair<int, int>& intersection,
                          std::vector<std::pair<char, int>>& wire_path) {

    int total_steps = 0;

    std::pair<int, int> curr_point = get_start_point();
    char direction;
    int steps;

    std::vector<std::pair<char, int>>::iterator it;
    for (it = wire_path.begin(); it != wire_path.end(); it++) {
        direction = it->first;
        steps = it->second;

        // std::set<std::pair<int, int>> segment;
        // segment = map_wire_segment(curr_point, direction, steps);

        std::pair<int, int> next_point;

        for (int i = 0; i < steps; i++) {
            if (direction == 'R') {
                next_point = right(curr_point);
            }
            if (direction == 'L') {
                next_point = left(curr_point);
            }
            if (direction == 'U') {
                next_point = up(curr_point);
            }
            if (direction == 'D') {
                next_point = down(curr_point);
            }
            curr_point = next_point;
            total_steps += 1;

            if (curr_point == intersection) {
                return total_steps;
            }
        }
    }
    return 0;
}

int find_minimum_steps(std::vector<std::pair<int, int>> intersection_list,
                       std::vector<std::pair<char, int>> wire_path_one,
                       std::vector<std::pair<char, int>> wire_path_two) {
    int min_steps = INT_MAX;

    for (auto &intersection : intersection_list) {
        int path_dist_A = calculate_total_steps(intersection, wire_path_one);
        int path_dist_B = calculate_total_steps(intersection, wire_path_two);

        int total_steps = path_dist_A + path_dist_B;

        bool shortest = (total_steps < min_steps);
        if (shortest) {
            min_steps = total_steps;
        }
    }
    return min_steps;
}

// DATA HANDLING FUNCTIONS
std::pair<char, int> split_data(std::string data) {
    char direction = data[0];  // Directions is always first character

    std::string step_str;
    int end = (data.length() - 1);  // Offset 1 for the direction character
    step_str.append(data, 1, end);
    int steps = stoi(step_str, nullptr);

    return  std::pair<char, int> (direction, steps);
}

// I was strugling with a clean way to get the data from block, to list of
// comma seperate values, to my expected data type.
// This solution seems hardcoded, but I got tired of messing with it.
void get_wire_paths(std::vector<std::string> parsed_data,
                    std::vector<std::pair<char, int>>& wire_path_one,
                    std::vector<std::pair<char, int>>& wire_path_two,
                    bool& success) {

    success = false;
    std::istringstream str_strm_one(parsed_data[0]);
    std::vector<std::pair<char, int>> local_data;
    std::string data;

    while (getline(str_strm_one, data, ',')) {
        std::pair<char, int> instruction = split_data(data);
        local_data.push_back(instruction);
    }
    wire_path_one = std::move(local_data);

    std::istringstream str_strm_two(parsed_data[1]);
    local_data.clear();

    while (getline(str_strm_two, data, ',')) {
        std::pair<char, int> instruction = split_data(data);
        local_data.push_back(instruction);
    }
    wire_path_two = std::move(local_data);
    success = true;
}

void parse_input_text(std::string input_path,
                      std::vector<std::string>* parsed_data,
                      bool& success) {
    success = false;
    std::ifstream input_file;
    input_file.open(input_path);

    if (input_file.is_open()) {
        std::vector<std::string> local_data;
        std::string data;

        while (getline(input_file, data, '\n')) {
            local_data.push_back(data);
        }
        *parsed_data = std::move(local_data);
        success = true;
    }
}

// SOLUTIONS
void solve_part_A() {
    std::string input_dir = "/Users/josh/repos/aoc-2019/day03/input.txt";  // personal mac

    std::vector<std::string> parsed_data;
    bool success = false;
    parse_input_text(input_dir, &parsed_data, success);

    if (!success) {
        printf("Error parsing file.\n");
        return;
    }
    printf("File parsed.\n");

    std::vector<std::pair<char, int>> wire_path_one;
    std::vector<std::pair<char, int>> wire_path_two;
    success = false;
    get_wire_paths(parsed_data, wire_path_one, wire_path_two, success);

    if (!success) {
        printf("Error getting wire paths.\n");
        return;
    }
    printf("Wire paths obtained.\n");

    int min_intersection;
    min_intersection = find_closest_intersection(wire_path_one, wire_path_two);
    printf("Part A Solution: %d\n", min_intersection);
}

void solve_part_B() {
    std::string input_dir = "/Users/josh/repos/aoc-2019/day03/input.txt";  // personal mac

    std::vector<std::string> parsed_data;
    bool success = false;
    parse_input_text(input_dir, &parsed_data, success);

    if (!success) {
        printf("Error parsing file.\n");
        return;
    }
    printf("File parsed.\n");

    std::vector<std::pair<char, int>> wire_path_one;
    std::vector<std::pair<char, int>> wire_path_two;
    success = false;
    get_wire_paths(parsed_data, wire_path_one, wire_path_two, success);

    if (!success) {
        printf("Error getting wire paths.\n");
        return;
    }
    printf("Wire paths obtained.\n");

    std::vector<std::pair<int, int>> intersection_list =
                            find_intersections(wire_path_one, wire_path_two);

    int min_steps = find_minimum_steps(intersection_list,
                                       wire_path_one,
                                       wire_path_two);
    printf("Part B Solution: %d\n", min_steps);
}

int main(int argc, char* argv[]) {
    solve_part_A();
    solve_part_B();
}
