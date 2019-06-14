# #easy #fibonacci_number
from sys import stdin

counts = [0] * 1001
counts[0] = 1
counts[1] = 2
for n in range(2, 1001):
    counts[n] = counts[n - 2] + counts[n - 1]

for n in stdin:
    print(counts[int(n)])
