# #easy
from sys import stdin

fibs = [0, 1]
while fibs[-1] < 10**1000:
    fibs.append(fibs[-2] + fibs[-1])

for line in stdin:
    print(fibs[int(line)])
