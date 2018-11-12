# #trivial
from sys import stdin

for line in stdin:
    n, a = map(int, line.split())
    sum, b = 0, 1
    for i in range(1, n + 1):
        b *= a
        sum += i * b
    print(sum)
