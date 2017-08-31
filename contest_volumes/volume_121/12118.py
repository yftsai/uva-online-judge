# #eulerian_path
def inspect(edges):
    n = next(iter(edges.keys()))
    edge_count = 0
    odd_count = len(edges[n]) % 2
    paths = set([n])
    while len(paths) > 0:
        n = next(iter(paths))
        paths.remove(n)
        if n in edges:
            for m in edges[n]:
                edge_count += 1
                if not m in paths:
                    paths.add(m)
                    odd_count += len(edges[m]) % 2
                if len(edges[m]) == 1:
                    del edges[m]
                else:
                    edges[m].remove(n)
            del edges[n]
    return edge_count + max(odd_count, 2)//2 - 1

case_count = 0
while True:
    v, e, t = map(int, input().split())
    if v == 0:
        break
    else:
        edges = dict()
        for _ in range(e):
            a, b = map(int, input().split())
            edges[a], edges[b] = edges.get(a, set()), edges.get(b, set())
            edges[a].add(b)
            edges[b].add(a)
        time = 0
        while len(edges) > 0:
            if time > 0:
                time += t
            time += t * inspect(edges)
        case_count += 1
        print("Case %d: %d" % (case_count, time))
