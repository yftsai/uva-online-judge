# #geometry
from math import atan2, pi
from bisect import bisect

def cprod(u, v):
    return u[0] * v[1] - u[1] * v[0]

def in_half_of(u, v):
    """Returns whether u is the half of [angle(v), angle(v) + pi)"""
    return u[0] == v[0] or cprod(v[1], u[1]) > 0

def cache(a, b, lines):
    x = b
    y = -a
    angle = atan2(y, x)
    if not angle in lines:
        lines[angle] = (a, b)

def validate(cherries, a, b):
    p, n = 0, 0
    for _, (x, y) in cherries:
        v = a * x + b * y
        assert v != 0, "Cherry (%d, %d) are not allowed on the beeline." % (x, y)
        if v > 0:
            p += 1
        else:
            n += 1
    assert p == n, "Halves have %d and %d cherries." % (p, n)

lines = {}
for a in range(-500, 500):
    for b in range(-500, 500):
        if a != 0 or b != 0:
            cache(a, b, lines)
for a in range(-500, -1):
    for b in range(0, 500):
        cache(a, b, lines)
langles = sorted(lines.keys())

a = langles[0]
lines[ a + 2 * pi ] = lines[a]
langles.append(a + 2 * pi)

while True:
    n = int(input())
    if n == 0:
        break
    two_n = 2 * n

    cherries = []
    for _ in range(two_n):
        x, y = map(int, input().split())
        a = atan2(y, x)
        cherries.append((a, (x, y)))
    cherries = sorted(cherries)

    b, c = 0, None      # A beeline cuts between cherries[b] and cherries[b + 1]
                        #       and cuts between cherries[c - 1] and cherries[c]
    ab = None
    while b < two_n and ab is None:
        while b + 1 < two_n and cherries[b][0] == cherries[b + 1][0]:
            b += 1
            if b == c: c = None

        if c == None: c = b + 1
        while c != b and in_half_of(cherries[c], cherries[(b + 1) % two_n]):
            c = (c + 1) % two_n

        if (c + two_n - b - 1) % two_n == n:
            c_1 = (c + two_n - 1) % two_n
            u = cherries[b][1]
            v = (-cherries[c_1][1][0], -cherries[c_1][1][1])
            lower = atan2(v[1], v[0]) if cprod(u, v) > 0 else cherries[b][0]
            i = bisect(langles, lower)
            if i < len(langles):
                ab = lines[ langles[i] ]
                vline = (ab[1], -ab[0])
                vb1 = cherries[(b + 1) % two_n][1]
                vc = cherries[c][1]
                vc_pi = (-vc[0], -vc[1])

                if cprod(vline, vb1) > 0 and cprod(vline, vc_pi) > 0:
                    break
                else:
                    ab = None

        b, c = b + 1, None if b + 1 == c else c

    print(ab[0], ab[1])
