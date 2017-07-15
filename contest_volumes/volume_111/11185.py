# #easy
from sys import stdin

for line in stdin:
    n = int(line)
    if n<0:
        break
    else:
        t = 0
        base = 1
        while n>0:
            t += base * (n%3)
            n//=3
            base *= 10
        print(t)
