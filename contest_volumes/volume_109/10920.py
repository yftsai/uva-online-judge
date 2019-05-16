# #easy
from math import sqrt, ceil

dirs = [(-1, 0), (0, -1), (1, 0), (0, 1)]

while True:
    sz, p = map(int, input().split())
    if sz == 0:
        break
    else:
        index = ceil(sqrt(p)) // 2
        inner_sz = 1 + 2 * index
        line = column = (sz + 1) // 2 + index
        q = inner_sz ** 2 - p

        for d in dirs:
            e = min(inner_sz - 1, q)
            line   += d[0] * e
            column += d[1] * e
            q -= e

        print("Line = %d, column = %d." % (line, column))
