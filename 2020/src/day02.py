#/bin/python3

import argparse
import sys


# BUSINESS LOGIC
def count_letter(letter, password):
    cnt = int()

    for char in password:
        cnt = (cnt + 1) if (char == letter) else cnt

    return cnt


def validate_old_password(flr, ceil, letter_count):
    is_valid = (flr <= letter_count and letter_count <= ceil)

    return is_valid


def count_valid_passwords_old(data_array):
    cnt = int()
    policy_array = policy_format_from_data_array(data_array)

    for flr, ceil, ltr, pw in policy_array:
        if (validate_old_password(flr, ceil, count_letter(ltr, pw))):
            cnt = cnt + 1

    return cnt


def validate_new_password(pos1, pos2, ltr, pw):
    idx1 = pos1 - 1  # -1 b/c policy has no concept of index zero
    idx2 = pos2 - 1

    if (pw[idx1] == pw[idx2] == ltr):
        return False
    elif (pw[idx1] == ltr):
        return True
    elif (pw[idx2] == ltr):
        return True

    return False


def count_valid_passwords_new(data_array):
    cnt = int()
    policy_array = policy_format_from_data_array(data_array)

    for pos1, pos2, ltr, pw in policy_array:
        if (validate_new_password(pos1, pos2, ltr, pw)):
            cnt = cnt + 1

    return cnt


# PARSING FUNCTIONS
def parse_policy(data):
    dash = int()
    blank = int()
    colon = int()

    for i in range(0, len(data)):
        if (data[i] == '-'):
            dash = i
        elif (blank == int() and data[i] == ' '):
            blank = i
        elif (data[i] == ':'):
            colon = i

    flr = int(data[:dash])
    ceil = int(data[dash+1:blank])  # +1 start index after dash
    ltr = data[blank+1:colon]  # +1 start index after blank
    pw = data[colon+2:]  # +2 start two indexes after colon

    return [flr, ceil, ltr, pw]


def policy_format_from_data_array(data_array):
    policy_array = list()

    for data in data_array:
        policy_array.append(parse_policy(data))

    return policy_array


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
def test_validate_new_password():
    pos1 = 1
    pos2 = 3
    ltr = 'a'
    pw = 'abcde'
    assert(validate_new_password(pos1, pos2, ltr, pw) is True)

    pos1 = 1
    pos2 = 3
    ltr = 'a'
    pw = 'zbade'
    assert(validate_new_password(pos1, pos2, ltr, pw) is True)

    pos1 = 1
    pos2 = 3
    ltr = 'b'
    pw = 'cdefg'
    assert(validate_new_password(pos1, pos2, ltr, pw) is False)

    pos1 = 2
    pos2 = 9
    ltr = 'c'
    pw = 'cccccccccc'
    assert(validate_new_password(pos1, pos2, ltr, pw) is False)

    pos1 = 1
    pos2 = 4
    ltr = 'c'
    pw = 'aaaaaa'
    assert(validate_new_password(pos1, pos2, ltr, pw) is False)


def test_validate_old_password():
    flr = 1
    ceil = 5
    count = 3
    assert(validate_old_password(flr, ceil, count) is True)

    flr = 1
    ceil = 5
    count = 0
    assert(validate_old_password(flr, ceil, count) is False)

    flr = 1
    ceil = 5
    count = 7
    assert(validate_old_password(flr, ceil, count) is False)


def test_count_letter():
    pw = "joshjoshjosh"
    ltr = 'j'

    assert(count_letter(ltr, pw) == 3)

    pw = "claudia"
    ltr = 'j'

    assert(count_letter(ltr, pw) == 0)


def test_parse_policy():
    data = "1-2 w: test1"
    [flr, ceil, ltr, pw] = parse_policy(data)

    assert(flr == 1)
    assert(ceil == 2)
    assert(ltr == 'w')
    assert(pw == 'test1')

    data = "9-10 h: test2"
    [flr, ceil, ltr, pw] = parse_policy(data)

    assert(flr == 9)
    assert(ceil == 10)
    assert(ltr == 'h')
    assert(pw == 'test2')

    data = "13-14 s: test3"
    [flr, ceil, ltr, pw] = parse_policy(data)

    assert(flr == 13)
    assert(ceil == 14)
    assert(ltr == 's')
    assert(pw == 'test3')


if __name__ == '__main__':
    # Unit testing
    test_parse_policy()
    test_count_letter()
    test_validate_old_password()
    test_validate_new_password()

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

    sol1 = count_valid_passwords_old(data_array)
    print("There are {:d} valid passwords in Part 1. \n".format(sol1))

    sol2 = count_valid_passwords_new(data_array)
    print("There are {:d} valid passwords in Part 2. \n".format(sol2))
