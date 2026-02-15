# #easy
for c in range(int(input())):
    _, h, ta, td = map(int, input().split())
    ns = sorted(map(int, input().split()))
    i, j = 0, len(ns) - 1
    t = 0
    if td < ta * 2:
        while i < j:
            if ns[j] >= h or ns[i] + ns[j] >= h:
                t += ta
                j -= 1
            elif ns[i] + ns[j] < h:
                t += td
                i += 1
                j -= 1
    t += ta * (j - i + 1)
    print("Case %d: %d" % (c + 1, t))
