# #shortest_path
while True:
    n, m = map(int, input().split())
    if n == 0:
        break
    else:
        edges = [ [] for _ in range(n) ]
        x, y, k = map(int, input().split())
        for _ in range(m):
            u, v, l = map(int, input().split())
            edges[u - 1].append((v - 1, l))

        lengths = [ [] for _ in range(n) ]
        qs = [ [] for _ in range(n) ]
        qs[x - 1].append(0)

        while len(lengths[y - 1]) < k and sum(len(q) for q in qs) > 0:
            nodes = filter(lambda i: len(qs[i]) > 0, range(n))
            node = min(nodes, key = lambda i: qs[i][-1])
            d = qs[node].pop()
            lengths[node].append(d)
            for e in edges[node]:
                m = e[0]
                qs[m].append(d + e[1])
                qs[m].sort()
                while len(lengths[m]) + len(qs[m]) > k:
                    qs[m].pop()
                qs[m].reverse()

        if len(lengths[y - 1]) < k:
            print(-1)
        else:
            print(lengths[y - 1][k - 1])
