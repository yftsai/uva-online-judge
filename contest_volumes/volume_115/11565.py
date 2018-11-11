# #easy
from math import sqrt

def search(a, b, c):
    xm = int(sqrt(c))
    for x in range(-xm, xm + 1):
        ym = int(sqrt(c - x**2))
        for y in range(max(-ym, x + 1), ym + 1):
            z = a - x - y
            if y < z and x * y * z == b and x**2 + y**2 + z**2 == c:
                return (x, y, z)
    return None

for _ in range(int(input())):
    a, b, c = map(int, input().split())
    solution = search(a, b, c)
    if solution == None:
        print('No solution.')
    else:
        print(' '.join(map(str, solution)))
