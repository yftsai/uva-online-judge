# #easy
from math import sqrt

while True:
    n = int(input())
    if n == 0:
        break
    else:
        m = int(sqrt(n))
        msq = m * m
        if n == msq:
            r, c = m, 1
        elif n <= msq + m + 1:
            r, c = (m + 1), (n - msq)
        else:
            r, c = (msq + m + m + 1 - n + 1), (m + 1)

        if m % 2 == 1:
            r, c = c, r
        print(r, c)
