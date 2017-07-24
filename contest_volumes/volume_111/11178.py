# #geometry #floating_point
# It's possible to achieve arbitrary precision by using Fraction, but its performance isn't good enough.
substract = lambda v1, v2: (v1[0] - v2[0], v1[1] - v2[1])
dot = lambda v1, v2: v1[0] * v2[0] + v1[1] * v2[1]
get_length2 = lambda v: v[0]**2 + v[1]**2

# given cos_3x = prod_3x / sqrt(length2_3x) and cos_y = prod_y / sqrt(length2_y), returns Ture if x < y.
def less_than(prod_3x, length2_3x, prod_y, length2_y):
    # y >= pi/2 or y >= pi/3 implies 3*y >= pi > 3*x
    if prod_y <= 0 or prod_y **2 * 4 <= 1 * length2_y:
        return True
    elif (prod_3x >= 0) != (prod_y **2 * 4 >= 3 * length2_y):
        return prod_3x >= 0

    cos_2_y  = prod_y **2 / length2_y
    cos_2_3y = 16 * cos_2_y**3 - 24 * cos_2_y **2 + 9 * cos_2_y     # cos(3*y) = 4 * cos(y)**3 - 3 * cos(y)

    return (prod_3x **2 > cos_2_3y * length2_3x) if prod_3x >= 0 else (prod_3x **2 < cos_2_3y * length2_3x)

# returns a point m. mb trisects angle abc. m is on ac and is closer to c.
def trisect(a, b, c):
    v_ba = substract(a, b)
    v_bc = substract(c, b)
    length2_bc = get_length2(v_bc)
    prod_ba_bc = dot(v_ba, v_bc)
    length2_ba_bc = get_length2(v_ba) * length2_bc

    m = a
    large, small = a, c
    for _ in range(32):
        m = ((large[0] + small[0]) /2, (large[1] + small[1]) /2)
        v_bm = substract(m, b)
        prod_bm_bc = dot(v_bm, v_bc)
        length2_bm_bc = get_length2(v_bm) * length2_bc
        if less_than(prod_ba_bc, length2_ba_bc, prod_bm_bc, length2_bm_bc):
            large = m
        else:
            small = m
    return m

for _ in range(int(input())):
    vs = list(map(int, input().split()))
    a = (vs[0], vs[1])
    b = (vs[2], vs[3])
    c = (vs[4], vs[5])
    d = trisect(trisect(a, b, c), c, b)
    e = trisect(trisect(b, c, a), a, c)
    f = trisect(trisect(c, a, b), b, a)
    print("%.6f %.6f %.6f %.6f %.6f %.6f" % (d[0], d[1], e[0], e[1], f[0], f[1]))
