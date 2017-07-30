# #maximum_flow #maximum_bipartite_matching
def augment(edges, loc, dst, path):
    if loc == dst:
        return True
    else:
        for i in range(len(edges[loc])):
            next = edges[loc][i]
            if not path[next]:
                path[next] = True
                edges[loc][i] = edges[loc][-1]
                edges[loc].pop()
                edges[next].append(loc)
                if augment(edges, next, dst, path):
                    return True
                else:
                    edges[loc].append(next)
                    edges[loc][i], edges[loc][-1] = edges[loc][-1], edges[loc][i]
                    edges[next].pop()
        return False

for t in range(int(input())):
    a = list(map(int, input().split()[1:]))
    b = list(map(int, input().split()[1:]))
    source = len(a) + len(b)
    sink = source + 1
    edges = [ list() for _ in range(sink + 1) ]
    edges[source] = list(range(len(a)))
    for i in range(len(a)):
        for j in range(len(b)):
            if (a[i] == 0 and b[j] == 0) or (a[i] != 0 and b[j] % a[i] == 0):
                edges[i].append(len(a) + j)
    for j in range(len(b)):
        edges[len(a) + j].append(sink)

    flow = 0
    while augment(edges, source, sink, [i==source for i in range(len(edges))]):
        flow += 1
    print("Case %d: %d"% (t + 1, flow))
