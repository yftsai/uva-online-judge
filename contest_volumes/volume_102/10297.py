# #geometry
from sys import stdin
from math import pi

def get_remaining_volume(r, s):
    return pi * (r ** 2 * s + r * (s - r) ** 2 + (s - r) ** 3 / 3) * 2

for line in stdin:
    d, v = map(int, line.split())
    if d == 0:
        break
    else:
        s = d / 2
        vol = pi * s ** 2 * d
        min_r, max_r = 0, s
        while min_r < max_r and (max_r - min_r) > 0.00001:
            r = (min_r + max_r) / 2
            w = vol - get_remaining_volume(r, s)
            if w < v:
                max_r = r
            else:
                min_r = r
        print("%.3f" % ((max_r + min_r)))
