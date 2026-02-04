# #easy
from math import factorial

while True:
    n = int(input())
    if n == 0:
        break

    counts = {}
    for d in map(int, input().split()):
        counts[d] = counts.get(d, 0) + 1

    facs = {}
    facs[n - 1] = factorial(n - 1)
    for c in counts.values():
        if c not in facs:
            facs[c] = factorial(c)
        if c - 1 not in facs:
            facs[c - 1] = factorial(c - 1)

    dsum = 0
    for d in counts:
        c = d * facs[n - 1]
        for e in counts:
            c //= facs[ counts[e] - 1 if d == e else counts[e] ]
        dsum += c

    s = 0
    for _ in range(n):
        s = s * 10 + dsum
    print(s)
