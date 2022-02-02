from cs50 import get_string, get_int
from sys import argv, exit



#with cs50
answer = get_string("Whats your name? ") # with cs50
answer2 = input("whats your name? ")     # without cs50
print("Hello, " + answer)
print(f"Hello, {answer2}")  #formatted string



counter = 0
counter += 1

x=0
y=1
if x < y:
    print("x is less than y")
elif x > y:
    print("y is less than x")
else:
    print("same")

#while True:
#    print("true")

i = 4
while i < 3:
    print("hello")
    i += 1

for i in [0, 1, 2]:
    print("hello")

for i in range(3):
    print("helllo, world")


##mini mario
for i in range(3):
    for j in range(3):
        print("#", end="")
    print()

## dynamically get user input and use it
scores= []
for i in range(3):
    scores.append(get_int("score: "))

average = sum(scores) / len(scores)
print(f"average: {average}")



#uppercasing and iterating over characters in a string
s = get_string("string: ")
for c in s:
    print(c.upper(), end="")
print()


#argv stuff from comman line
if len(argv) == 2:
    print(f"hello, {argv[1]}")
else:
    print("hello, world")


##exit statuses with sys.argv and sys.exit
if len(argv) != 2:
    print("missing command line argument")
    exit(1)

print(f"hello, {argv[1]}")
exit(0)

 
##defining a dict 
people = {
    "Brian" : "+1-800-111-111"
    "David" : "+1-123-123-123"
}

#fiddling with it
#note that when you do search in, it only searches the keys not the values
#dictionaries in python use hash functions!!
name = get_string("name: ")
if name in people:
    number  = people[name]
    print(f"number: {number}")

#swapping variables
x=1
y=2
x, y = y, x

##writing with csv files, assuming you currently have a .csv file in directory 
import csv

with open("phonebook.csv", "a") as file:

    name = get_string("name: ")
    number = get_string("number: ")
    
    writer = csv.writer(file)
    
    writer.writerow([name, number])


## doing some easy stats with a .csv poll result
##harry potter houses poll
import csv
houses = {
    "Gryff": 0,
    "Slyth": 0,
    "Raven": 0,
    "Huffle": 0,
}

with open("nameofcsv.csv", "r") as file:
    reader = csv.reader(file)
    next(reader) #skips first line
    for row in reader:
        house = row[1]
        houses[house] += 1
        
for house in houses:
    print(f"{house}: {houses[house]}")






