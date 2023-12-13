import csv
import sys


def main():
    # Check for the correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read the database file into a variable
    database_filename = sys.argv[1]
    with open(database_filename, newline="") as csv_file:
        reader = csv.DictReader(csv_file)
        data = list(reader)

    # Read the DNA sequence file into a variable
    sequence_filename = sys.argv[2]
    with open(sequence_filename, "r") as sequence_file:
        dna_sequence = sequence_file.read()

    # Find the longest match of each STR in the DNA sequence
    str_counts = {
        key: longest_match(dna_sequence, key) for key in data[0].keys() if key != "name"
    }

    # Check the database for matching profiles
    for row in data:
        match = all(int(str_counts[key]) == int(row[key]) for key in str_counts)
        if match:
            print(row["name"])
            return

    # If no match is found, print "No match"
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of the longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    i = 0
    while i < len(sequence):
        count = 0
        while sequence[i : i + subsequence_length] == subsequence:
            count += 1
            i += subsequence_length
        longest_run = max(longest_run, count)
        i += 1
    return longest_run


if __name__ == "__main__":
    main()
