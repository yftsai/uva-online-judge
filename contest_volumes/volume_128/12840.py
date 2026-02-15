# #dynamic_programming
for cno in range(int(input())):
    n, s = map(int, input().split())
    ps = list(map(int, input().split()))

    counts = [0] * s
    for i in range(n):
        p = ps[i]
        counts[p - 1] = 1
        for j in range(p, s):
            if counts[j - p] > 0:
                c = counts[j - p] + 1
                counts[j] = min(c, counts[j]) if counts[j] > 0 else c

    if counts[-1] == 0:
        print("Case %d: impossible" % (cno + 1))
    else:
        points = []
        for i in range(n - 1, -1, -1):
            p = ps[i]
            while s == p or (s > p and counts[s - p - 1] + 1 == counts[s - 1]):
                points.append(p)
                s -= p
        print("Case %d: [%d] %s" % (cno + 1, len(points), " ".join(map(str, points))))
