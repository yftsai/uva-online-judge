# #geometry
from math import sqrt, acos, pi, sin

add = lambda p, q: (p[0] + q[0], p[1] + q[1])
minus = lambda p, q: (p[0] - q[0], p[1] - q[1])
scale = lambda v, s: (v[0] * s, v[1] * s)
get_distance = lambda v: sqrt(v[0] * v[0] + v[1] * v[1])
dot_product = lambda p, q: p[0] * q[0] + p[1] * q[1]

try:
    while True:
        m = (float(input()), float(input()))
        n = int(input())

        p = (float(input()), float(input()))
        vpm = minus(m, p)
        dpm = get_distance(vpm)

        r, d = p, dpm
        for _ in range(n):
            q = (float(input()), float(input()))
            vqm = minus(m, q)
            dqm = get_distance(vqm)
            if dqm < d:
                r, d = q, dqm

            if dpm > 0 and p != q:
                vpq = minus(q, p)
                dpq = get_distance(vpq)
                a = acos(dot_product(vpm, vpq) / dpm / dpq)
                e = dpm * sin(a)

                if e < d:
                    v = scale((-vpq[1], vpq[0]), dpm * sin(a) / dpq)
                    s = min(add(m, v), minus(m, v), key = lambda s: get_distance(minus(p, s)))
                    if get_distance(minus(s, p)) <= dpq and get_distance(minus(s, q)) <= dpq:
                        r, d = s, e

            p, vpm, dpm = q, vqm, dqm
        print("%.4f" % r[0])
        print("%.4f" % r[1])
except:
    pass
