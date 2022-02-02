# Credit, this time in Python

while True:
    try:
        card = input('Number: ')
        if int(card) < 0:
            raise ValueError  # make sure input is in range
        break
    except ValueError:  # make sure input is numerical
        print("INVALID")

length = len(card)
evenSum = 0
oddSum = 0

for i in range(length - 2, -1, -2):  # sum digits of product of every other number, starting from second to last
    product = (int(card[i])*2)
    if product < 10:
        evenSum = evenSum + product
    else:
        evenSum = evenSum + int((str(product))[0]) + int((str(product))[1])

for i in range(length - 1, -1, -2):  # sum remaining digits 
    oddSum = oddSum + (int(card[i]))

if ((evenSum + oddSum) % 10) != 0:  # check if sum of even and odd digits are mod 10
    print("INVALID")
    exit(1)

if length == 16: 
    if int(card[0]) == 4:  # Visa: 13/16digits, start with 4
        print("VISA")
        exit(0)
    elif int(card[0]) == 5 and int(card[1]) in range(1, 6):  # Master: 16digits, start with 51-55

        print("MASTERCARD")
        exit(0)
    else:
        print("INVALID")
        exit(1)

if length == 13 and int(card[0]) == 4:
    print("VISA")
    exit(0)

# Amex: 15digits, start with 34 or 37
if length == 15: 
    if int(card[0]) == 3 and (int(card[1]) == 4 or int(card[1]) == 7):
        print("AMEX")
    else:
        print("INVALID")
        exit(1)
