import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def _get_frequencies(): #Reads from file to count number of times each word occurs.
    counts = {}
    with open("GroceryInput.txt", "r") as f:
        for line in f:
            line = line.rstrip().lower()
            counts[line] = counts.get(line, 0) + 1
    return counts

def PrintCounts(): #Prints the word and the count of the word.
    counts = _get_frequencies()
    for k, v in counts.items():
        print("{}: {}".format(k, v))

def GetCountForWord(word): #Returns a count for a given word search.
    counts = _get_frequencies()
    return counts.get(word.lower(), 0)

def StoreFrequencyData(): #Takes frequency from input file and writes to frequency.dat
    counts = _get_frequencies()
    with open("frequency.dat", "w") as f:
        for k, v in counts.items():
            f.write("{} {}\n".format(k, v))