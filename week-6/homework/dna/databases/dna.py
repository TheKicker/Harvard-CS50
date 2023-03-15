import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("USAGE: python dna.py [csv path] [dna path]")
    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as csv_file:
        reader = list(csv.reader(csv_file))
        reader[0].remove("name")
        index = reader[0]
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dna_file:
        data = dna_file.read()
    # TODO: Find longest match of each STR in DNA sequence
    values = []
    for i in range(len(index)):
        max_count = 0
        count = 0
        position = 0
        previous_position = 0
        next_position = 0

        while position < len(data):
            position = data.find(index[i], position)

            if position == -1:
                count = 0
                break
            elif (position != -1) and previous_position == 0:
                count += 1
                max_count = count
                previous_position = position
                next_position = position + 1
            elif (position != -1) and ((position - len(index[i])) == previous_position):
                count += 1
                previous_position = position
                if max_count < count
                    max_count = count
                next_position = position + 1
            elif (position != -1) and ((position - len(index[i])) != previous_position):
                count = 1
                previous_position = position
                if max_count < count
                    max_count = count
                next_position = position + 1
            position += 1
        values.push(max_count)
    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
