# #geometry
from math import acos

negative = lambda v: (-v[0], -v[1])
add = lambda v, w: (v[0] + w[0], v[1] + w[1])
multiply = lambda v, s: (v[0] * s, v[1] * s)
length = lambda v: (v[0] **2 + v[1] **2) **0.5
dprod = lambda v, w: v[0] * w[0] + v[1] * w[1]
cprod = lambda v, w: v[0] * w[1] - v[1] * w[0]

# returns the signed area of opq within radius r
def get_area(p, q, r):
    lp, lq = length(p), length(q)

    if lq <= r:
        if lp <= r:
            return 0.5 * cprod(p, q)
        else:
            return -get_area(q, p, r)
    elif lp == r:
        return r **2 /2 * acos(dprod(p, q) /lp /lq) * (1 if cprod > 0 else -1)
    else:
        vpq = add(q, negative(p))
        o = add(p, multiply(vpq, dprod(negative(p), vpq) / length(vpq) **2))
        if lp < r:
            voq = add(q, negative(o))
            c = add(o, multiply(voq, (r**2 - length(o)**2) **0.5 / length(voq)))
            dprod_cq = dprod(c, q)
            return 0.5 * cprod(p, c) + r **2 /2 * acos(dprod_cq / r / lq) * (1 if cprod(p, q) > 0 else -1)
        elif length(o) >= r:
            return r **2 /2 * acos(dprod(p, q) /lp /lq) * (1 if cprod(p, q) > 0 else -1)
        else:
            return get_area(p, o, r) + get_area(o, q, r)

def get_overlapped_area(polygon, r):
    return sum(get_area(polygon[i], polygon[(i + 1) % len(polygon)], r) for i in range(len(polygon)))

case_number = 0
while True:
    nr = input().split()
    if nr[0] == "0":
        break
    else:
        r = float(nr[1])
        polygon = []
        for _ in range(int(nr[0])):
            polygon.append(tuple(map(float, input().split())))

        radius = (0, max(length(p) for p in polygon))
        a = get_overlapped_area(polygon, radius[1])
        if a > 0:
            area = (0, a)
        else:
            polygon = polygon[::-1]
            area = (0, -a)

        while radius[1] - radius[0] > 0.0002:
            # interpolation to shrink the range of raiduses within 1
            int_r = radius[0] + (radius[1] - radius[0]) * ((r - area[0]) / (area[1] - area[0])) **0.5
            for delta in range(-4, 5):
                int_rd = int_r + delta / 10
                if radius[0] < int_rd and int_rd < radius[1]:
                    a = get_overlapped_area(polygon, int_rd)
                    radius = (int_rd, radius[1]) if a < r else (radius[0], int_rd)
                    area = (a, area[1]) if a < r else (area[0], a)
            # binary search to guarantee the precision improvement
            mid_r = sum(radius) / len(radius)
            a = get_overlapped_area(polygon, mid_r)
            radius = (mid_r, radius[1]) if a < r else (radius[0], mid_r)
            area = (a, area[1]) if a < r else (area[0], a)

        case_number += 1
        print("Case %d: %.2f" % (case_number, sum(radius) / len(radius)))
