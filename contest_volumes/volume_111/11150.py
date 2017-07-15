# #trivial
from sys import stdin

for line in stdin:
    n = int(line)
    bottle_count = n
    while n >= 3:
        bottle_count += n//3
        n = n//3 + n%3
    if n == 2:
        bottle_count += 1
    print(bottle_count)
