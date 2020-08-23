from sys import argv, exit
from csv import DictReader

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

STRs = []

data = open(argv[1], "r")
reader = DictReader(data)
for row in reader:
    for key in row.keys():
        if (key == 'name') or (key in STRs):
            continue
        else:
            STRs.append(key)

file = open(argv[2], "r")
seq = file.read()


def countReps(index, strLength, STR):
    if seq[index:index + strLength] != STR:
        return 0
    else:
        return 1 + countReps(index + strLength, strLength, STR)


strCount = {}
for STR in STRs:
    maxCount = 0
    for index in range(len(seq)):
        reps = countReps(index, len(STR), STR)
        if reps > maxCount:
            maxCount = reps

    strCount[STR] = maxCount

# I can't access the database again, so I had to explicitly declare it again down below.
data = open(argv[1], "r")
reader = DictReader(data)

matched = False
for row in reader:
    sameCount = 0
    for key in strCount.keys():
        if int(strCount[key]) == int(row[key]):
            sameCount += 1

    if sameCount == len(STRs):
        print(row['name'])
        matched = True
        break

if matched:
    exit(0)
else:
    print("No match.")