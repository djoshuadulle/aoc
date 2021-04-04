#/bin/python3

import argparse
import numpy as np
import sys


def count_trees(slope_map, rise, run):
    cnt = int()

    slope_idxs = generate_rows_cols(slope_map, rise, run)

    for row, col in slope_idxs:
        if slope_map[row][col] == '#':
            cnt = cnt + 1

    return cnt


def generate_rows_cols(slope_map, rise, run):
    slope_idxs = list()
    row = 0
    col = 0

    num_rows, num_cols = slope_map.shape

    for i in range(0, num_rows - 1, rise):
        row = row + rise
        col = (col + run) % num_cols

        slope_idxs.append((row, col))

    return slope_idxs


def make_slope_map(data_array):
    slope_map = list()

    for data in data_array:
        row = list()

        for char in data:
            row.append(char)

        slope_map.append(row)

    return np.array(slope_map)


def parse_file(input_path: str):
    data_array = list()

    try:
        with open(input_path, "r") as file:
            for data in file:
                data = data[:-1]
                data_array.append(data)
    except IOError:
        return None

    return data_array


# UNIT TESTS


if __name__ == '__main__':
    # Unit testing

    # The arg parser lets you pass in arguments from the command line
    # and creates --help documentation.
    parser = argparse.ArgumentParser(description="Parameters to run script.")
    parser.add_argument("--input_path", help="Location of input file.")
    args = parser.parse_args()

    # Not required, but good practice to check that the user passed in
    # good data before using it.
    if args.input_path is None:
        sys.exit("Enter the location of input file.")

    # Get data out of input file.
    data_array = parse_file(args.input_path)

    if data_array is None:
        print("Error parsing file.")
    # Else we know the data is good and may safely call our functions.

    rise = 1
    run = 3
    treesA = count_trees(make_slope_map(data_array), rise, run)
    print("Number of trees encountered on slope {:d}, {:d} is: {:d}".format(
        rise, run, treesA))

    run = 1
    rise = 1
    treesB = count_trees(make_slope_map(data_array), rise, run)
    print("Number of trees encountered on slope {:d}, {:d} is: {:d}".format(
        rise, run, treesB))

    run = 5
    rise = 1
    treesC = count_trees(make_slope_map(data_array), rise, run)
    print("Number of trees encountered on slope {:d}, {:d} is: {:d}".format(
        rise, run, treesC))

    run = 7
    rise = 1
    treesD = count_trees(make_slope_map(data_array), rise, run)
    print("Number of trees encountered on slope {:d}, {:d} is: {:d}".format(
        rise, run, treesD))

    run = 1
    rise = 2
    treesE = count_trees(make_slope_map(data_array), rise, run)
    print("Number of trees encountered on slope {:d}, {:d} is: {:d}".format(
        rise, run, treesE))

    product = treesA * treesB * treesC * treesD * treesE
    print("Product of number of trees encountered on each slope is: {:d}".format(product))
