# #easy
from math import sqrt

case_number = 1
while True:
    n = int(input())
    if n == 0:
        break
    else:
        s = max(4, int(sqrt(n * 2)))
        print("Case %d: %d" % (case_number, next(m for m in range(s, s + 5) if n <= m * (m - 3) // 2)))
        case_number += 1
