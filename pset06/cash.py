from cs50 import get_float

c = -1

while c < 0:
    c = round(100 * get_float("Change owed: "))
    # handlig more than 2 digits after points by round f and *100

coins = 0
# counting needed coins

while c >= 25:  # counting quartes
    c -= 25
    coins += 1

while c >= 10:  # counting dimes
    c -= 10
    coins += 1

while c >= 5:  # counting 5 cents
    c -= 5
    coins += 1

while c >= 1:  # counting pennies
    c -= 1
    coins += 1

print(coins)