# #geometry
from math import pi, sin

while True:
    n, r = map(int, input().split())
    if r == 0:
        break
    else:
        angles = sorted(float(input()) / 180 * pi for _ in range(n))
        area = 0
        for i in range(len(angles)):
            for j in range(i + 1, len(angles)):
                area += sin(angles[j] - angles[i]) * (n - 2 * j + 2 * i)
        print(round(r * r * area / 2))
