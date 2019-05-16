# #easy
from sys import stdin
from math import atan, tan, pi

for line in stdin:
    l, w, h, a = map(float, line.split())
    a = a / 180 * pi
    b = atan(h / l)
    if a < b:
        volume = (l * h - tan(a) * l * l / 2) * w
    else:
        volume = h / tan(a) * h / 2 * w
    print('%.3f mL' % volume)
