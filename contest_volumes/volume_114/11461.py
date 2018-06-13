# #easy
from math import sqrt, ceil
from sys import stdin
from bisect import bisect_left, bisect_right

sqnums = [i**2 for i in range(1, ceil(sqrt(10**5)))]

for line in stdin:
    a, b = map(int, line.split())
    if a == 0:
        break
    else:
        print(bisect_right(sqnums, b) - bisect_left(sqnums, a))
