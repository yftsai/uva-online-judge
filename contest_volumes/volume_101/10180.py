# #geometry
from math import acos
negate = lambda v: (-v[0], -v[1])
add = lambda v, w: (v[0] + w[0], v[1] + w[1])
get_length = lambda v: (v[0] **2 + v[1] **2) **0.5
dot = lambda v, w: v[0] * w[0] + v[1] * w[1]

for _ in range(int(input())):
    x1, y1, x2, y2, r = map(float, input().split())
    p, q = (x1, y1), (x2, y2)
    v_pq = add(negate(p), q)

    if v_pq == (0, 0):
        rope_length = 0
    else:
        d_pc = dot(negate(p), v_pq) / get_length(v_pq)
        if 0 < d_pc and d_pc < get_length(v_pq) and max(0, get_length(p) **2 - d_pc **2) **0.5 < r:
            a = acos(max(-1, min(1, dot(p, q) / get_length(p) / get_length(q))))
            a -= acos(min(1, r / get_length(p))) + acos(min(1, r / get_length(q)))
            rope_length = max(0, get_length(p) **2 - r **2) **0.5 + r * a + max(0, get_length(q) **2 - r **2) **0.5
        else:
            rope_length = get_length(v_pq)

    print("%.3f" % rope_length)
