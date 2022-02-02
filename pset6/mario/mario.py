# Mario more

while True:
    try:
        height = int(input('Height: '))
        if height not in range(1, 9):
            raise ValueError  # make sure input is in range
        break
    except ValueError:  # make sure input is numerical
        print("Invalid integer. The number must be in the range of 1-9.")    

for i in range(1, height + 1):
    print((" " * (height - i)) + ("#" * i) + "  " + ("#" * i))