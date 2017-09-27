# #convex_hull
evaluate = lambda line, p: line[0] * p[0] + line[1] * p[1] + line[2]

def cut(convex, line):
    n = len(convex)
    i = max(range(n), key = lambda i: evaluate(line, convex[i]))
    if evaluate(line, convex[i]) <= 0:
        return []
    else:
        c = [ convex[i] ]
        for j in range(n):
            p, q = convex[(i + j) % n], convex[(i + j + 1) % n]
            if evaluate(line, p) * evaluate(line, q) < 0:
                v = (q[0] - p[0], q[1] - p[1])
                scale = - evaluate(line, p) / (line[0] * v[0] + line[1] * v[1])
                c.append((p[0] + scale * v[0], p[1] + scale * v[1]))

            if evaluate(line, q) >= 0:
                c.append(q)
        c.pop()
        return c

from fractions import Fraction
for t in range(int(input())):
    input()
    it = map(Fraction, input().split())
    convex = [ (next(it), next(it)) for _ in range(3)]
    it = map(Fraction, input().split())
    points = [ (next(it), next(it)) for _ in range(3)]

    for i in range(3):
        p, q, r = points[i], points[(i + 1) % 3], points[(i + 2) % 3]
        slope = None if p[0] == q[0] else ((q[1] - p[1]) / (q[0] - p[0]))
        line = (1, 0, -p[0]) if slope == None else (slope, -1, -(slope *  p[0] - p[1]))

        if evaluate(line, r) < 0:
            line = tuple(-v for v in line) if evaluate(line, r) < 0 else line
        elif evaluate(line, r) == 0:
            convex = []

        if len(convex) == 0:
            break
        else:
            convex = cut(convex, line)

    print("pair %d: %s" % (t + 1, "no" if len(convex) == 0 else "yes"))
