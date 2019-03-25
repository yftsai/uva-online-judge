# #trivial
from sys import stdin

for line in stdin:
    line = ''.join(map(lambda c: c if c.isalpha() else "", line))
    length = len(line)
    if line == 'DONE':
        break
    elif all(line[i].lower() == line[length - 1 - i].lower() for i in range(length // 2)):
        print("You won't be eaten!")
    else:
        print("Uh oh..")
