#calculus #floating_point
from sys import stdin
from math import acos, ceil

eps = 0.00000001

def eval_func(a, x):
    v = 0
    base = 1
    for ai in a:
        v += base * ai
        base *= x
    return v

def binary_search(a, xlow, xhigh, v):
    if round(xhigh, 2) - round(xlow, 2) < 0.01 - eps:
        return xlow
    else:
        xmid = (xhigh + xlow)/2
        vmid = eval_func(a, xmid)
        return binary_search(a, xmid, xhigh, v) if vmid < v else binary_search(a, xlow, xmid, v)

case = 0
while stdin.readline():
    case += 1
    line = stdin.readline()
    a = list(map(float, line.split()))
    line = stdin.readline()
    xlow, xhigh, inc = map(float, line.split())

    pi = acos(-1)
    b = [0 for i in range(0, len(a) * 2 - 1)]
    for i in range(0, len(a)):
        for j in range(0, len(a)):
            b[i + j] += a[i] * a[j] * pi

    # integral
    c = [ b[i]/(i+1) for i in range(0, len(b))]
    c[0:0] = [0]
    c[0] = -eval_func(c, xlow)

    vol = eval_func(c, xhigh)
    mark = []
    for i in range(1, 9):
        if i*inc > vol + eps:
            break
        else:
            mark.append("{:.2f}".format(binary_search(c, xlow, xhigh, i*inc) - xlow))

    print("Case {:d}: {:.2f}".format(case, vol))
    if len(mark) == 0:
        print("insufficient volume")
    else:
        print(" ".join(mark))
