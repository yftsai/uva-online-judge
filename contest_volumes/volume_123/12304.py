# #geometry
from sys import stdin
from math import acos, atan2, asin, cos, degrees, pi, sin

def middle_of(p, q):
    return ((p[0] + q[0]) / 2, (p[1] + q[1]) / 2)

def vector_of(p, q):
    return (q[0] - p[0], q[1] - p[1])

def orthogonal_of(v):
    return (-v[1], v[0])

def lensq(v):
    return v[0] * v[0] + v[1] * v[1]

def length_of(v):
    return (v[0] ** 2 + v[1] ** 2) ** 0.5

def dot(u, v):
    return u[0] * v[0] + u[1] * v[1]

def cprod(u, v):
    return u[0] * v[1] - u[1] * v[0]

def add(u, v):
    return (u[0] + v[0], u[1] + v[1])

def scale(u, s):
    return (u[0] * s, u[1] * s)

def fix_angle(r):
    while r >= pi:
        r -= pi
    while r < 0:
        r += pi
    return r

# p + v * s == q + u * t
#   v.x * s - u.x * t = q.x - p.x
#   v.y * s - u.y * t = q.y - p.y
def intersect(p, v, q, u):
    rhsx = q[0] - p[0]
    rhsy = q[1] - p[1]
    cs = v[0] * u[1] - v[1] * u[0]
    ct = -u[0] * v[1] + u[1] * v[0]
    if abs(cs) > abs(ct):
        s = (rhsx * u[1] - rhsy * u[0]) / cs
        return (p[0] + v[0] * s, p[1] + v[1] * s)
    else:
        t = (rhsx * v[1] - rhsy * v[0]) / ct
        return (q[0] + u[0] * t, q[1] + u[1] * t)

def print_angles(angles):
    angles = sorted(map(lambda r: degrees(fix_angle(r)), angles))
    print("[" + ",".join(map(lambda a: "%.6f" % a, sorted(angles))) + "]")

def print_centers(points):
    print("[" + ",".join(map(lambda p: "(%.6f,%.6f)" % (p[0], p[1]), sorted(points))) + "]")

for line in stdin:
    prob, *coord = line.split()
    if prob == 'CircumscribedCircle':
        x1, y1, x2, y2, x3, y3 = map(int, coord)
        p1, p2, p3 = (x1, y1), (x2, y2), (x3, y3)
        m12 = middle_of(p1, p2)
        v12 = vector_of(p1, p2)
        m23 = middle_of(p2, p3)
        v23 = vector_of(p2, p3)
        c = intersect(m12, orthogonal_of(v12), m23, orthogonal_of(v23))
        r = length_of(vector_of(p1, c))
        print("(%.6f,%.6f,%.6f)" % (c[0], c[1], r))
    elif prob == 'InscribedCircle':
        x1, y1, x2, y2, x3, y3 = map(int, coord)
        p1, p2, p3 = (x1, y1), (x2, y2), (x3, y3)
        v12 = vector_of(p1, p2)
        v13 = vector_of(p1, p3)
        v21 = vector_of(p2, p1)
        v23 = vector_of(p2, p3)
        sign = 1 if cprod(v12, v23) > 0 else -1
        a12 = atan2(v12[1], v12[0])
        a = acos(dot(v12, v13) / length_of(v12) / length_of(v13)) / 2
        a1 = atan2(v12[1], v12[0]) + sign * a
        a2 = atan2(v23[1], v23[0]) + sign * acos(dot(v21, v23) / length_of(v21) / length_of(v23)) / 2
        c = intersect(p1, (cos(a1), sin(a1)), p2, (cos(a2), sin(a2)))
        vp1c = vector_of(p1, c)
        print("(%.6f,%.6f,%.6f)" % (c[0], c[1], length_of(vp1c) * sin(a)))
    elif prob == 'TangentLineThroughPoint':
        xc, yc, r, xp, yp = map(int, coord)
        pc, pp = (xc, yc), (xp, yp)
        vpc = vector_of(pp, pc)
        lsq_pc = lensq(vpc)
        if lsq_pc < r * r:
            print_angles([])
        elif lsq_pc == r * r:
            print_angles([ atan2(-vpc[0], vpc[1]) ])
        else:
            a = atan2(vpc[1], vpc[0])
            b = asin(r / lsq_pc ** 0.5)
            print_angles([a - b, a + b])
    elif prob == 'CircleThroughAPointAndTangentToALineWithRadius':
        xp, yp, x1, y1, x2, y2, r = map(int, coord)
        pp, p1, p2 = (xp, yp), (x1, y1), (x2, y2)
        v12 = vector_of(p1, p2)
        pq = intersect(p1, v12, pp, orthogonal_of(v12))
        vpq = vector_of(pp, pq)
        lpq = length_of(vpq)
        if lpq > 2 * r:
            print_centers([])
        elif lpq == 0:
            l12 = length_of(v12)
            v = (-v12[1] * r / l12, v12[0] * r / l12)
            print_centers([add(pp, v), add(pp, scale(v, -1))])
        elif length_of(vpq) == 2 * r:
            print_centers([ add(pp, scale(vpq, 0.5)) ])
        else:
            d = (r ** 2 - (r - lpq) ** 2) ** 0.5
            s = d / length_of(v12)
            v = scale(vpq, -r / lpq)
            cs = [add(pq, scale(v12, s)), add(pq, scale(v12, -s))]
            print_centers(map(lambda p: add(p, v), cs))
    elif prob == 'CircleTangentToTwoLinesWithRadius':
        x1, y1, x2, y2, x3, y3, x4, y4, r = map(int, coord)
        p1, p2, p3, p4 = (x1, y1), (x2, y2), (x3, y3), (x4, y4)
        v12 = vector_of(p1, p2)
        v34 = vector_of(p3, p4)
        m = intersect(p1, v12, p3, v34)
        if cprod(v12, v34) < 0:
            v12, v34 = v34, v12
        a1 = atan2(v12[1], v12[0])
        a = acos(dot(v12, v34) / length_of(v12) / length_of(v34)) / 2
        v = scale((cos(a1 + a), sin(a1 + a)), r / sin(a))
        a2 = atan2(v34[1], v34[0])
        b = acos(dot(scale(v12, -1), v34) / length_of(v12) / length_of(v34)) / 2
        u = scale((cos(a2 + b), sin(a2 + b)), r / sin(b))
        print_centers([ add(m, v), add(m, scale(v, -1)), add(m, u), add(m, scale(u, -1)) ])
    else:
        x1, y1, r1, x2, y2, r2, r = map(int, coord)
        p1, p2 = (x1, y1), (x2, y2)
        v12 = vector_of(p1, p2)
        lensq12, lensqlimit = lensq(v12), (r1 + r2 + r * 2) ** 2
        if lensq12 > lensqlimit:
            print_centers([])
        elif lensq12 == lensqlimit:
            len12 = lensq12 ** 0.5
            print_centers([add(p1, scale(v12, (r1 + r) / len12))])
        else:
            len12 = lensq12 ** 0.5
            d = (r1 ** 2 + 2 * r1 * r - r2 ** 2 - 2 * r2 * r + lensq12) / 2 / len12
            e = scale(orthogonal_of(v12), ((r1 + r) ** 2 - d ** 2) ** 0.5 / len12)
            m = add(p1, scale(v12, d / len12))
            print_centers([add(m, e), add(m, scale(e, -1))])
