# #eulerian_path
from sys import stdin

def add_edge(graph, v, w):
    graph[v] = graph.get(v, dict())
    graph[v][w] = graph[v].get(w, 0) + 1
    graph[w] = graph.get(w, dict())
    graph[w][v] = graph[w].get(v, 0) + 1

def del_edge(graph, v, w):
    graph[v][w] -= 1
    if graph[v][w] == 0: del graph[v][w]
    if not graph[v]: del graph[v]
    graph[w][v] -= 1
    if graph[w][v] == 0: del graph[w][v]
    if not graph[w]: del graph[w]

def find_cycle(graph, vertices, cycle):
    while vertices:
        v = cycle[-1] if len(cycle) > 0 and cycle[0] != cycle[-1] else next(iter(vertices), None)
        edges = graph.get(v, None) if v else None

        # impossible to extend from v
        if edges == None:
            vertices.remove(v)
        # extending the cycle from the middle
        elif cycle[-1] != v:
            i = cycle.index(v)
            cycle = cycle[i:-1] + cycle[:i+1]   # inefficient but acceptable
        # extending the cycle from its tail
        else:
            w = next(iter(edges.keys()))
            del_edge(graph, v, w)
            if graph.get(v, None): vertices.add(v)
            cycle.append(w)
    return cycle

t = int(stdin.readline())
for case in range(1, t+1):
    n = int(stdin.readline())
    graph = dict()
    for _ in range(0, n):
        v, w = map(int, stdin.readline().split())
        add_edge(graph, v, w)

    v = next(iter(graph.keys()))
    cycle = [] if any([sum(edges.values())%2 != 0 for edges in graph.values()]) else find_cycle(graph, set([v]), [v])

    if case > 1:
        print()
    print("Case #", case, sep = '')
    if len(cycle) == 0 or cycle[0] != cycle[-1]:
        print("some beads may be lost")
    else:
        for i in range(0, len(cycle)-1):
            print(cycle[i], cycle[i+1])
