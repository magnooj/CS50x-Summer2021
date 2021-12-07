from cs50 import get_int
# definig height
h = 0

# getting input
while h < 1 or h > 8:
    h = get_int("Height: ")

# printing columns
for i in range(1, h+1):
    print(" " * (h - i) + "#" * i, end="  ")
    print("#" * i)