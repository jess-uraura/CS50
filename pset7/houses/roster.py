from cs50 import SQL
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python roster.py <house>")
    exit(1)

db = SQL("sqlite:///students.db")
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = :house ORDER BY last, first", house=argv[1])
for student in students:
    if student['middle'] == None:
        print(f"{student['first']} {student['last']}, born {student['birth']}")
    else:
        print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")