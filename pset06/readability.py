t = input("Text: ").lower().strip()
""" debuging by printing t """
#print (t)

# setting counters
letter = 0
word = 1
sent = 0

# calculating by for loop in list of string t.
for i in t:
    if (i == " "):
        word += 1
    elif i in [".", "!", "?"]:
        sent += 1
    elif (i.isalpha()):
        letter += 1

""" debuging with this print func: """
#print(f"letter {letter}, word {word}, sentence {sent}")

# calculating coleman index
L = letter / word * 100
S = sent / word * 100
grade = round(0.0588 * L - 0.296 * S - 15.8)

# printing result
if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")