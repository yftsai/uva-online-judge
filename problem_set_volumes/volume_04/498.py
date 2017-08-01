from sys import stdin
from functools import reduce

cs = None
for line in stdin:
    if cs == None:
        cs = list(map(int, line.split()))
    else:
        xs = list(map(int, line.split()))
        print(" ".join(map(str, (reduce(lambda a, c: a*x + c, cs) for x in xs))))
        cs = None
