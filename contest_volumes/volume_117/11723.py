# #trivial
from sys import stdin
from math import ceil

case_number = 1
for line in stdin:
    r, n = map(int, line.split())
    if n > 0:
        d = 0 if r <= n else (ceil(r / n) - 1)
        print("Case %d: %s" % (case_number, str(d) if d <= 26 else "impossible"))
        case_number += 1
