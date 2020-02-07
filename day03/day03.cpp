#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <map>
#include <set>
#include <vector>
#include <climits>

const std::pair<int, int> CENTRAL_PORT(0, 0);

const std::pair<int, int> get_start_point() {
    return CENTRAL_PORT;
}

std::pair<int, int> get_last_point(const std::set<std::pair<int, int>>& segment,
                                   const char& direction) {
    bool positive_move = (direction == 'R' || direction == 'U');
    bool negative_move = (direction == 'L' || direction == 'D');
    std::pair<int, int> last_point;

    if (positive_move) {
    // Because sets order from smallest to biggest, e.g. -10, ..., 0, ..., 10
    // positive moves from (0, 0) result in the last element being the end point
        std::set<std::pair<int, int>>::reverse_iterator end_pt;
        end_pt = segment.rbegin();
        last_point = *end_pt;
    }

    if (negative_move) {
    // Because sets order from smallest to biggest, e.g. -10, ..., 0, ..., 10
    // negative moves from (0, 0) result in the first element being the end point
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

int get_manhattan_distance(const std::pair<int, int>& pointA, const std::pair<int, int>& pointB) {
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

        curr_point = get_last_point(segment, direction);
        full_path.insert(segment.begin(), segment.end());
    }
    return full_path;
}

int find_closest_intersection(std::vector<std::pair<char, int>>& wire_path_A,
                              std::vector<std::pair<char, int>>& wire_path_B) {

    std::set<std::pair<int, int>> full_path_A;
    full_path_A = map_wire_path(wire_path_A);

    std::set<std::pair<int, int>> full_path_B;
    full_path_B = map_wire_path(wire_path_B);

    int manhattanDistance = INT_MAX;
    for (auto const &pt: full_path_A) {
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

// UNIT TESTS

int testDirections() {
    std::pair<int, int> curr_point;
    curr_point.first = 0;
    curr_point.second = 0;
    std::pair<int, int> next_point = right(curr_point);
    assert(next_point.first == 1);
    assert(next_point.second == 0);

    curr_point = next_point;
    next_point = up(curr_point);
    assert(next_point.first == 1);
    assert(next_point.second == 1);

    curr_point = next_point;
    next_point = left(curr_point);
    assert(next_point.first == 0);
    assert(next_point.second == 1);

    curr_point = next_point;
    next_point = down(curr_point);
    assert(next_point.first == 0);
    assert(next_point.second == 0);

    return 0;
}

int testManhattanDistance() {
    std::pair<int, int> pointA;
    pointA.first = 9;    // x1
    pointA.second = 11;  // y1

    std::pair<int, int> pointB;
    pointB.first = 3;    // x2
    pointB.second = 2;   // y2

    int quadrantOneDistance = get_manhattan_distance(pointA, pointB);
    assert(quadrantOneDistance == 15);

    pointA.first = -7;   // x1
    pointA.second = 11;  // y1

    pointB.first = -3;   // x2
    pointB.second = 2;   // y2

    int quadrantTwoDistance = get_manhattan_distance(pointA, pointB);
    assert(quadrantTwoDistance == 13);

    pointA.first = -9;    // x1
    pointA.second = -11;  // y1

    pointB.first = -8;    // x2
    pointB.second = -2;   // y2

    int quadrantThreeDistance = get_manhattan_distance(pointA, pointB);
    assert(quadrantThreeDistance == 10);

    pointA.first = 9;     // x1
    pointA.second = -11;  // y1

    pointB.first = 3;    // x2
    pointB.second = -11; // y2

    int quadrantFourDistance = get_manhattan_distance(pointA, pointB);
    assert(quadrantFourDistance == 6);

    return 0;
}

int testMapWireSegment() {
    char direction;
    int steps;

    std::set<std::pair<int, int>> segment;
    size_t segment_length;

    std::pair<int, int> last_point;
    int last_x;
    int last_y;

    // Right
    direction = 'R';
    steps = 75;

    segment = map_wire_segment(CENTRAL_PORT, direction, steps);

    segment_length = segment.size();
    assert(segment_length == 75);

    last_point = get_last_point(segment, direction);
    last_x = last_point.first;
    last_y = last_point.second;
    assert(last_x == 75);
    assert(last_y == 0);

    // Up
    direction = 'U';
    steps = 83;

    segment = map_wire_segment(CENTRAL_PORT, direction, steps);

    segment_length = segment.size();
    assert(segment_length == 83);

    last_point = get_last_point(segment, direction);
    last_x = last_point.first;
    last_y = last_point.second;
    assert(last_x == 0);
    assert(last_y == 83);

    // Left
    direction = 'L';
    steps = 12;

    segment = map_wire_segment(CENTRAL_PORT, direction, steps);

    segment_length = segment.size();
    assert(segment_length == 12);

    last_point = get_last_point(segment, direction);
    last_x = last_point.first;
    last_y = last_point.second;
    assert(last_x == -12);
    assert(last_y == 0);

    // Down
    direction = 'D';
    steps = 30;

    segment = map_wire_segment(CENTRAL_PORT, direction, steps);

    segment_length = segment.size();
    assert(segment_length == 30);

    last_point = get_last_point(segment, direction);
    last_x = last_point.first;
    last_y = last_point.second;
    assert(last_x == 0);
    assert(last_y == -30);

    return 0;
}

const std::vector<std::pair<char, int>> get_wire_path_A() {
    // R75,D30,R83,U83,L12,D49,R71,U7,L72
    std::vector<std::pair<char, int>> wire_path_A = {
        std::pair<char, int> ('R', 75),
        std::pair<char, int> ('D', 30),
        std::pair<char, int> ('R', 83),
        std::pair<char, int> ('U', 83),
        std::pair<char, int> ('L', 12),
        std::pair<char, int> ('D', 49),
        std::pair<char, int> ('R', 71),
        std::pair<char, int> ('U', 7),
        std::pair<char, int> ('L', 72),
    };
    return wire_path_A;
}

const std::vector<std::pair<char, int>> get_wire_path_B() {
    // U62,R66,U55,R34,D71,R55,D58,R83
    std::vector<std::pair<char, int>> wire_path_B = {
        std::pair<char, int> ('U', 62),
        std::pair<char, int> ('R', 66),
        std::pair<char, int> ('U', 55),
        std::pair<char, int> ('R', 34),
        std::pair<char, int> ('D', 71),
        std::pair<char, int> ('R', 55),
        std::pair<char, int> ('D', 58),
        std::pair<char, int> ('R', 83)
    };
    return wire_path_B;
}

const std::vector<std::pair<char, int>> get_wire_path_C() {
    // R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
    std::vector<std::pair<char, int>> wire_path_C = {
        std::pair<char, int> ('R', 98),
        std::pair<char, int> ('U', 47),
        std::pair<char, int> ('R', 26),
        std::pair<char, int> ('D', 63),
        std::pair<char, int> ('R', 33),
        std::pair<char, int> ('U', 87),
        std::pair<char, int> ('L', 62),
        std::pair<char, int> ('D', 20),
        std::pair<char, int> ('R', 33),
        std::pair<char, int> ('U', 53),
        std::pair<char, int> ('R', 51)
    };
    return wire_path_C;
}

const std::vector<std::pair<char, int>> get_wire_path_D() {
    // U98,R91,D20,R16,D67,R40,U7,R15,U6,R7
    std::vector<std::pair<char, int>> wire_path_D = {
        std::pair<char, int> ('U', 98),
        std::pair<char, int> ('R', 91),
        std::pair<char, int> ('D', 20),
        std::pair<char, int> ('R', 16),
        std::pair<char, int> ('D', 67),
        std::pair<char, int> ('R', 40),
        std::pair<char, int> ('U', 7),
        std::pair<char, int> ('R', 15),
        std::pair<char, int> ('U', 6),
        std::pair<char, int> ('R', 7)
    };
    return wire_path_D;
}

void testMapWirePath() {
    std::vector<std::pair<char, int>> wire_path = get_wire_path_A();

    std::set<std::pair<int, int>> full_path;
    full_path = map_wire_path(wire_path);

    for (auto const &pt: full_path) {
        printf("x: %d, y: %d\n", pt.first, pt.second);
    }
}

int testFindClosestIntersection() {
    std::vector<std::pair<char, int>> wire_path_A = get_wire_path_A();
    std::vector<std::pair<char, int>> wire_path_B = get_wire_path_B();
    std::vector<std::pair<char, int>> wire_path_C = get_wire_path_C();
    std::vector<std::pair<char, int>> wire_path_D = get_wire_path_D();

    int intersect_distance;

    intersect_distance = find_closest_intersection(wire_path_A, wire_path_B);
    assert(intersect_distance == 159);

    intersect_distance = find_closest_intersection(wire_path_C, wire_path_D);
    assert(intersect_distance == 135);

    return 0;
}


void printResults(const int& result) {
    if (result == 0) {
        printf("Success!\n");
    } else {
        printf("Fail!\n");
    }
}

int main(int argc, char* argv[]) {
    printResults(testManhattanDistance());
    printResults(testDirections());
    printResults(testMapWireSegment());
    printResults(testFindClosestIntersection());
    // testMapWirePath();
}
