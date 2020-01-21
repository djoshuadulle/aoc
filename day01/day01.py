#/bin/python3

import argparse
import math
import sys


parser = argparse.ArgumentParser(description="Parameters to run script.")
parser.add_argument("--input_dir", help="Location of directory containing input.")
args = parser.parse_args()

if args.input_dir is None:
    sys.exit("You must enter the location of fuel requirements.")

file_dir = "{dir}".format(dir=args.input_dir)
fuel_total = 0

try:
    with open(file_dir, "r") as file:
        for module in file:
            module_fuel_req = math.floor(float(module)/3) - 2
            added_fuel_req = math.floor(float(module_fuel_req)/3) - 2
            while (added_fuel_req > 0):
                module_fuel_req += added_fuel_req
                added_fuel_req = math.floor(float(added_fuel_req)/3) - 2
            fuel_total += module_fuel_req
    sys.exit("The total fuel requirement is {:f}.".format(fuel_total))
except IOError as e:
    print(e)
    sys.exit("Ensure the location of fuelreq.txt is correct.")
