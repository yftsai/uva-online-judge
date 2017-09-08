# #shortest_path
from queue import PriorityQueue

def get_shortest_distances(outs, s, d):
    distances = [-1] * len(outs)
    is_shortest = [False] * len(outs)
    distances[s] = 0
    q = PriorityQueue()
    q.put((0, s))
    while not q.empty():
        d, u = q.get()
        if not is_shortest[u]:
            is_shortest[u] = True
            for v in outs[u]:
                e = d + outs[u][v]
                if distances[v] < 0 or e < distances[v]:
                    distances[v] = e
                    q.put((e, v))
    return distances

def inverse(outs):
    ins = [dict() for _ in outs]
    for u in range(len(outs)):
        for v in outs[u]:
            ins[v][u] = outs[u][v]
    return ins

def remove_shortest_paths(ins, s, v, distances, d):
    us = list(ins[v].keys())
    for u in us:
        if u in ins[v] and distances[u] + ins[v][u] == d:
            del ins[v][u]
            remove_shortest_paths(ins, s, u, distances, distances[u])

while True:
    n, m = map(int, input().split())
    if n == 0:
        break
    else:
        s, d = map(int, input().split())
        outs = [dict() for _ in range(n)]
        for _ in range(m):
            u, v, p = map(int, input().split())
            outs[u][v] = p

        distances = get_shortest_distances(outs, s, d)
        if distances[d] > 0:
            ins = inverse(outs)
            remove_shortest_paths(ins, s, d, distances, distances[d])
            outs = inverse(ins)
            distances = get_shortest_distances(outs, s, d)

        print(distances[d])
