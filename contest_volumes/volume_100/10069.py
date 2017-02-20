# #dynamic_programming
from sys import stdin

n = int(stdin.readline())
for _ in range(0, n):
    x = stdin.readline()
    z = stdin.readline()

    count = [1 if z[0] == xc else 0 for xc in x] if len(z) > 0 else []
    for zi in range(1, len(z)):
        c = [0 for _ in x]
        s = 0
        for xi in range(0, len(x)):
            if z[zi] == x[xi]: c[xi] = s
            s += count[xi]
        count = c

    print(sum(count))
