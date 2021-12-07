import csv
from sys import argv
""" I've got inspired with solution of this video:
https://www.youtube.com/watch?v=OEdH4Xd7M8M"""


def main():
    # check number of arguments
    if (len(argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")

    # Open files
    databasefile = open("./" + argv[1])
    givendna = open("./" + argv[2])

    # getting STRs
    database = csv.DictReader(databasefile)
    strs = database.fieldnames[1:]

    # copy DNAs in to a string
    dna = givendna.read()
    givendna.close()

    # counting number of repeated STRs
    dna_fingerprints = {}
    for s in strs:
        dna_fingerprints[s] = repeats(s, dna)

    # searching for person by fingerprints
    for line in database:
        # If there is a match
        if match(strs, dna_fingerprints, line):
            print(f"{line['name']}")
            databasefile.close()
            return

    # If there is no match
    print("No match")
    databasefile.close()


def repeats(s, dna):  # counting the maximum repeats of STRs
    i = 0
    while s * (i + 1) in dna:
        i += 1
    return i


def match(strs, dna_fingerprints, line):  # finding the match in database
    for s in strs:
        if dna_fingerprints[s] != int(line[s]):
            return False

    return True


# Starting program
main()