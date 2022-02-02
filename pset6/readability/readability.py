# Readability, this time in python

text = input("Text: ")

letters = 0
for s in text:
    if s.isalpha() == True:
        letters += 1

words = len(text.split())
sentences = text.count('.') + text.count('!') + text.count('?')

score = (0.0588 * ((letters/words)*100)) - (0.296 * ((sentences/words)*100)) - 15.8

if score < 1:
    print("Before Grade 1")
elif score > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(score)}")

# Measure: Letters, Words, Sentences
# Coleman-Liau: 0.0588 * L - 0.296 * S - 15.8
# where L is letters/100 words
# and   S is sentences/100 words
