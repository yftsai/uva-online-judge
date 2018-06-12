# #trivial
from sys import stdin

for n in stdin:
    n = int(n)
    if n == 0:
        break
    else:
        print("f91(%d) = %d" % (n, 91 if n <= 101 else n - 10))
