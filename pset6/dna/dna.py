# DNA Python Script

import csv
import sys

# Ensure correct usage
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py database.csv dna_sequence.csv")

people = []
# TODO: Read teams into memory from file sas dictionaries
filename = sys.argv[1]
with open(filename, 'r') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        match = row
        people.append(row)

with open(sys.argv[2], 'r') as file:
    sequence = file.read()

STRcount = []

for i in range(1, len(reader.fieldnames)):
    STR = reader.fieldnames[i]
    STRcount.append(0)
    
    for j in range(len(sequence)):
        # if match found, start counting repeats 
        counter = 0
        if sequence[j: (j + len(STR))] == STR:
            
            # start counting repeats
            STRstart = 0
            
            while sequence[(j + STRstart): (j + STRstart + len(STR))] == STR:
                counter += 1
                STRstart += len(STR)
            # if current counter greater than current max count, update and add to array
            if counter > STRcount[i - 1]:
                STRcount[i - 1] = counter
                

# If all STR counts in database match measured ones, return name of person, otherwise No match
for i in range(len(people)):
    hits = 0
    for j in range(1, len(reader.fieldnames)):
        if int(STRcount[j - 1]) == int(people[i][reader.fieldnames[j]]):
            hits += 1
        if hits == (len(reader.fieldnames) - 1):
            print(people[i]['name'])
            exit()
print("No match")
