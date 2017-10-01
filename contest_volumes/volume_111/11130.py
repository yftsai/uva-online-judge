# #trivial
from math import sin, cos, pi

while True:
    a, b, v, angle, s = map(int, input().split())
    if a == 0:
        break
    else:
        c = a /2 + v * s /2 *cos(angle /180 *pi)
        d = b /2 + v * s /2 *sin(angle /180 *pi)
        print(int(c /a), int(d /b))
