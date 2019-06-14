from sys import stdin

for line in stdin:
    m, n = map(int, line.split())
    if m == 0 and n == 0:
        break
    else:
        r, c = (m, n) if m <= n else (n, m)

        if r == 1:
            count = c
        elif r == 2:
            count = c // 4 * 4 + min(c % 4, 2) * 2
        else:
            count = (r * c + 1) // 2

        print("%d knights may be placed on a %d row %d column board." % (count, m, n))
