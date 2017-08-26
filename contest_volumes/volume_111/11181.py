# #probability #easy #dynamic_programming
from fractions import Fraction

def probability(ps, r):
    if len(ps) < r:
        return 0
    else:
        table = [1]
        for p in ps:
            if len(table) < r + 1:
                table.append(0)
            for i in range(len(table) - 1, 0, -1):
                table[i] = table[i] * (1-p) + table[i-1] * p
            table[0] *= (1-p)
        return table[r]

case_number = 0
while True:
    n, r = map(int, input().split())
    if n == 0:
        break
    else:
        ps = list()
        for _ in range(n):
            ps.append(Fraction(input()))
        case_number += 1
        print("Case %d:" % case_number)
        for i in range(n):
            ps[i], ps[-1] = ps[-1], ps[i]
            p = ps[-1]
            ps.pop()
            q = 0 if r == 0 else (probability(ps, r-1) * p)
            ps.append(p)
            ps[i], ps[-1] = ps[-1], ps[i]
            s = probability(ps, r)
            print("%.6f" % (q / s))
