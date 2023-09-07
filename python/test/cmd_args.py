# cmd_args.py
# run like $ python cmd_args.py Python Command Line Arguments

import sys

if __name__ == "__main__":
    print(f"Arguments count: {len(sys.argv)}")
    for i, arg in enumerate(sys.argv):
        print(f"Argument {i:>6}: {arg}")

print(f"Name of the script      : {sys.argv[0]}")

print(f"Arguments of the script : {sys.argv[1:]}")
