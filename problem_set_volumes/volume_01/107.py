#geometric_sequence
from sys import stdin
from math import log

for line in stdin:
    h, n_worker = map(int, line.split())
    if h == 0:
        break
    elif h == 1:
        print(0, 1)
    else:
        pred = lambda n, ah = h, aw = 1: (ah == 1 and aw == n_worker) if ah % (n+1) > 0 or aw > n_worker else pred(n, ah//(n+1), aw*n)
        n = next(filter(pred, range(1, h+1)))
        n_nonworker = (n_worker-1)//(n-1) if n > 1 else int(log(h, n+1))
        total_height = (n+1)*h - n*n_worker
        print(n_nonworker, total_height)
