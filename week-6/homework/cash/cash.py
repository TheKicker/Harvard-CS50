# TODO
from cs50 import get_float

# count is a better name for the variable, im confusing myself internally
change = 0
count = 0

while change <= 0:
    change = get_float("Change owed: ")
    cents = round(change*100)

while cents > 0:
    # if cents >= 50:
    #     cents = cents - 50
    #     count += 1
    if cents >= 25:
        cents = cents - 25
        count += 1
    elif cents >= 10:
        cents = cents - 10
        count += 1
    elif cents >= 5:
        cents = cents - 5
        count += 1
    elif cents >= 1:
        cents = cents - 1
        count += 1

print(count)

# 0.41 outputs 4
# 0.01 outputs 1
# 0.15 outputs 2
# UPDATE: I didin't pay attention and 50 cent pieces arent available
# 1.60 outputs 4
# 23 outputs 46
