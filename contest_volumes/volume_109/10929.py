# #trivial
from sys import stdin

for number in stdin:
    number = number.strip()
    if number == "0":
        break
    else:
        remainder = 0
        for c in number:
            remainder = (remainder * 10 + int(c)) % 11
        print("%s is%s a multiple of 11." % (number, "" if remainder == 0 else " not"))
