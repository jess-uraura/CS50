from cs50 import SQL
from csv import reader
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python import.py file.csv")
    exit(1)

db = SQL("sqlite:///students.db")

with open(argv[1], "r") as file:
    reader = reader(file)
    for row in reader:
        split, house, birth = row[0].split(), row[1], row[2]

        if len(split) == 3:
            first, middle, last = split[0], split[1], split[2]
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (:first, :middle, :last, :house, :birth)",
                        first=first, middle=middle, last=last, house=house, birth=birth)
        elif len(split) == 2:
            first, middle, last = split[0], None, split[1]
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (:first, :middle, :last, :house, :birth)",
                        first=first, middle=middle, last=last, house=house, birth=birth)