# #easy

from math import gcd
gs = [1]
for n in range(3, 501):
    gs.append(gs[-1])
    for i in range(1, n):
        gs[-1] += gcd(i, n)

from sys import stdin
for n in stdin:
    n = int(n)
    if n == 0:
        break
    else:
        print(gs[n - 2])
