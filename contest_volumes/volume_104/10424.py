# #trivial
from sys import stdin

n = None
for name in stdin:
    s = sum((ord(c) - ord('a') + 1) for c in name.lower() if c.isalpha())
    while s >= 10:
        t = 0
        while s > 0:
            t += s % 10
            s //= 10
        s = t

    if n == None:
        n = s
    else:
        print("%.2f %%" % (100 * min(n, s) / max(n, s)))
        n = None
