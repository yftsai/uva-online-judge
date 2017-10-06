# #geometry #easy
from sys import stdin
from math import pi, sin

for line in stdin:
    s, a, unit = line.split()
    r = 6440 + int(s)
    a = (int(a) / 60 if unit == 'min' else int(a)) / 180 * pi
    a -= (a // (2 * pi)) * 2 * pi       # floor division
    a = a if a <= pi else (2 * pi - a)
    print("%.6f %.6f" % (r * a, sin(a / 2) * r * 2))
