#/bin/python3

import argparse
import sys


def parse_file(input_path: str):
    # This makes an empty array (called list in Python)
    data_array = list()

    # The try catch here allows the program to fail gracefully
    # by catching the error thrown if the file can't be opened for some reason
    try:
        with open(input_path, "r") as file:
            # Iterates through each line of data in the file
            for data in file:
                # Removes the final character which is '/n',
                # the new line character, i.e. "enter"
                data = data[:-1]
                data_array.append(data)
    except IOError:
        return False, None

    # Python is crazy and lets you return as many things as you want,
    # and it is OK if the types are different.
    # This isn't necessarily the best way, but I am returning
    # True if success along with the array of data, and
    # False if parsing fails (None just means no data, i.e. Null)
    return True, data_array


def fix_expense_report_two_val(data_array):
    '''
    Traditionally a for loop would look like:
    for (int i = 0, i < length(data_array) - 1, i++)
    (Here the minus 1 is because indexing starts at zero, not one.)

    But Python is mad intuitive, so it lets you do iteration
    like above in parse file. Or... you can iterate from range(start, end).
    So this for loop starts at i = 0 and ends at i = length of data_array - 1.
    (Here the minus 1 is because I am comparing the last two indexes i and j,
    so I don't need the i to reach the last index in the array.)
    '''
    for i in range(0, len(data_array)-1):
        for j in range(i + 1, len(data_array)):
            val1 = int(data_array[i])  # This int() is a "cast" that turns the
            val2 = int(data_array[j])  # string data type into an int data type

            summation = val1 + val2

            if (summation == 2020):
                # Returning will stop the loop and exit the function
                return val1 * val2

    # Technically you will never get here, but good practice to signal failure
    return -1


def fix_expense_report_three_val(data_array):
    for i in range(0, len(data_array)-2):
        for j in range(i + 1, len(data_array)-1):
            for k in range(i + 2, len(data_array)):
                val1 = int(data_array[i])
                val2 = int(data_array[j])
                val3 = int(data_array[k])

                summation = val1 + val2 + val3

                if (summation == 2020):
                    return val1 * val2 * val3

    return -1


# These testing methods are here as an example of how to unit test,
# i.e. test the individual parts of the code.
# To make them fail, change the values in the data array.
def test_fix_expense_report_two_val():
    # If we provide these two values, we would expect the result to be:
    # 2000 * 20 = 40,000
    data_array = [2000, 20]

    sol = fix_expense_report_two_val(data_array)
    return (sol == 40000)  # Will return boolean, True or False


def test_fix_expense_report_three_val():
    # If we provide these three values, we would expect the result to be:
    # 1500 * 500 * 20 = 15,000,000
    data_array = [1500, 500, 20]

    sol = fix_expense_report_three_val(data_array)
    assert(sol == 15000000)  # assert() fails if False


if __name__ == '__main__':
    # Example unit testing
    if test_fix_expense_report_two_val() is False:
        # sys.exit() stops the program.
        sys.exit("Unit test for two val expense report failed!")

    # If the test fails, the assert() method will kill the program.
    test_fix_expense_report_three_val()

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
    success, data_array = parse_file(args.input_path)

    if not success:
        print("Error parsing file.")
    # Else we know the data is good and may safely call our functions.

    sol1 = fix_expense_report_two_val(data_array)
    # Recall -1 is the fail case and '!' means 'NOT'
    # so if the solution is NOT -1, we know we succeeded
    if sol1 != -1:
        print("The corrected expense report value is: {:d} \n".format(sol1))

    sol2 = fix_expense_report_three_val(data_array)
    if sol2 != -1:
        print("The corrected expense report value is: {:d} \n".format(sol2))
