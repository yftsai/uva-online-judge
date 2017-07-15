# #geometry
# The selected formulae are not biased by the selection of a, b, or c.
# Otherwise, the precision may be affected by their relative values.
from sys import stdin
from math import pi, sqrt

for line in stdin:
    a, b, c = map(int, line.split())

    area_triangle = sqrt((a+b+c) *(a+b-c) *(a-b+c) *(-a+b+c) /16)
    area_inner = (area_triangle *2 /(a+b+c))**2 *pi
    area_outer = (a *b *c /4 /area_triangle)**2 *pi

    print("%.4f %.4f %.4f" % (area_outer - area_triangle, area_triangle - area_inner, area_inner))
