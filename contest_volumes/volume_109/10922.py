# #trivial
from sys import stdin

def check(ds):
    degree = 0
    while len(ds) > 1:
        s, ds = sum(ds), []
        while s > 0:
            ds.append(s % 10)
            s //= 10
        degree += 1

    return max(1, degree) if ds[0] == 9 else 0

for n in stdin:
    n = n.rstrip()
    ds = [int(d) for d in n if d.isdigit()]
    if ds == [0]:
        break
    else:
        degree = check(ds)
        if degree == 0:
            print("%s is not a multiple of 9." % n)
        else:
            print("%s is a multiple of 9 and has 9-degree %d." % (n, degree))
