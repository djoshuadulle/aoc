#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <map>
#include <set>
#include <vector>


const std::pair<int, int> CENTRAL_PORT(0, 0);

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

int manhattanDistance(const std::pair<int, int>& pointA, const std::pair<int, int>& pointB) {
    int x_distance = abs(pointB.first - pointA.first);
    int y_distance = abs(pointB.second - pointA.second);
    int manhattanDistance = x_distance + y_distance;

    return manhattanDistance;
}

// Q: Is there a convention for chars as 'n' vs "n"?
std::set<std::pair<int, int>> mapWireSegment(const std::pair<int, int>& start_point,
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

// set<std::pair<int, int>>  mapWirePath(const std::vector<std::pair<char, int>>& wire_path) {
//     set<std::pair<int, int>> path_points;
//     path_points.insert(start_point);



//     std::vector<int>::iterator it;
//     for (it= wire_path.begin(); it != wire_path.end(); it++) {

//     }
//     return path_points;
// }

    // for (auto const &e: segment) {
    //     int x = e.first;
    //     int y = e.second;
    //     printf("x: %d, y: %d \n", x, y);
    // }


    // std::set<int> odd = { 1, 3, 5 };
    // std::set<int> even = { 2, 4, 6 };

    // std::set<int> s;
    // std::merge(odd.begin(), odd.end(),
    //             even.begin(), even.end(),
    //             std::inserter(s, s.begin()))

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

    int quadrantOneDistance = manhattanDistance(pointA, pointB);
    assert(quadrantOneDistance == 15);

    // std::pair<int, int> pointA;
    pointA.first = -7;   // x1
    pointA.second = 11;  // y1

    // std::pair<int, int> pointB;
    pointB.first = -3;   // x2
    pointB.second = 2;   // y2

    int quadrantTwoDistance = manhattanDistance(pointA, pointB);
    assert(quadrantTwoDistance == 13);

    // std::pair<int, int> pointA;
    pointA.first = -9;    // x1
    pointA.second = -11;  // y1

    // std::pair<int, int> pointB;
    pointB.first = -8;    // x2
    pointB.second = -2;   // y2

    int quadrantThreeDistance = manhattanDistance(pointA, pointB);
    assert(quadrantThreeDistance == 10);

    // std::pair<int, int> pointA;
    pointA.first = 9;    // x1
    pointA.second = -11;  // y1

    // std::pair<int, int> pointB;
    pointB.first = 3;    // x2
    pointB.second = -11;   // y2

    int quadrantFourDistance = manhattanDistance(pointA, pointB);
    assert(quadrantFourDistance == 6);

    return 0;
}

int testmapWireSegment() {
    char direction;
    int steps;

    std::set<std::pair<int, int>> segment;
    size_t segment_length;
    int end_x;
    int end_y;

    // Because sets order from smallest to biggest, e.g. -10, ..., 0, ..., 10
    // positive moves from (0, 0) result in the last element being the end point
    std::set<std::pair<int, int>>::reverse_iterator end_pt;

    // Right
    direction = 'R';
    steps = 75;

    segment = mapWireSegment(CENTRAL_PORT, direction, steps);

    segment_length = segment.size();
    assert(segment_length == 75);

    end_pt = segment.rbegin();
    end_x = end_pt->first;
    end_y = end_pt->second;
    assert(end_x == 75);
    assert(end_y == 0);

    // Up
    direction = 'U';
    steps = 83;

    segment = mapWireSegment(CENTRAL_PORT, direction, steps);

    segment_length = segment.size();
    assert(segment_length == 83);

    end_pt = segment.rbegin();
    end_x = end_pt->first;
    end_y = end_pt->second;
    assert(end_x == 0);
    assert(end_y == 83);

    // Because sets order from smallest to biggest, e.g. -10, ..., 0, ..., 10
    // negative moves from (0, 0) result in the first element being the end point
    std::set<std::pair<int, int>>::iterator beg_pt;

    // Left
    direction = 'L';
    steps = 12;

    segment = mapWireSegment(CENTRAL_PORT, direction, steps);

    segment_length = segment.size();
    assert(segment_length == 12);

    beg_pt = segment.begin();
    end_x = beg_pt->first;
    end_y = beg_pt->second;
    assert(end_x == -12);
    assert(end_y == 0);

    // Down
    direction = 'D';
    steps = 30;

    segment = mapWireSegment(CENTRAL_PORT, direction, steps);

    segment_length = segment.size();
    assert(segment_length == 30);

    beg_pt = segment.begin();
    end_x = beg_pt->first;
    end_y = beg_pt->second;
    assert(end_x == 0);
    assert(end_y == -30);

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
    printResults(testmapWireSegment());
}
