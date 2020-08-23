while True:
    credit = input("Number: ")
    if credit.isdigit():
        break

if len(credit) in (13, 15, 16):
    reversedCredit = credit[::-1]

    multiplied = str()
    for digit in reversedCredit[1::2]:
        multiplied += str(int(digit) * 2)

    notMultiplied = reversedCredit[::2]

    digitSum = sum(int(digit) for digit in multiplied) + sum(int(digit) for digit in notMultiplied)

    if (digitSum % 10) == 0:
        if credit[0] == "3" and (credit[1] == "4" or credit[1] == "7"):
            print("AMEX")
        elif credit[0] == "5" and (int(credit[1]) in range(1, 6)):
            print("MASTERCARD")
        elif credit[0] == "4":
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")