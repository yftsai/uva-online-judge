# #combinatorics
from sys import stdin

count = {1: 2}
count[2] = 1 + 2*count[1]
count[3] = 1 + count[1] + 2*count[2]

for n in range(4, 1001):
    count[n] = count[n-3] + count[n-2] + 2*count[n-1]

for line in stdin:
    print(count[int(line)])
