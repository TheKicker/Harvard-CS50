# TODO
from cs50 import get_int


while True:
    #location location location
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break
for row in range(height):
    # iterate through the row, start at zero, and decrement the code by 1
    for space in range(height - row - 1, 0, -1):
        # the end="" just removes the default line from pythons print function
        print(" ", end="")
    for hash in range(row + 1):
        # the end="" just removes the default line from pythons print function
        print("#", end="")
    # the end="" just removes the default line from pythons print function
    print("\n", end="")


