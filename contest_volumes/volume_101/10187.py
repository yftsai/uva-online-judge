# #shortest_path
from queue import PriorityQueue

for test_number in range(1, int(input()) + 1):
    edges = dict()
    for _ in range(int(input())):
        src, dst, dept, t = input().split()
        if not src in edges:
            edges[src] = dict()
        if not dst in edges[src]:
            edges[src][dst] = set()

        dept, t = int(dept), int(t)
        if dept <= 6 and dept + t <= 6:
            edges[src][dst].add((dept + 24, t))
        elif dept >= 18 and dept + t <= 24 + 6:
            edges[src][dst].add((dept, t))

    start, destination = input().split()
    distances = dict()
    distances[start] = (0, 18)  # blood, time
    q = PriorityQueue()
    q.put((0, 18, start))
    while not q.empty():
        blood, time, src = q.get()
        if (blood, time) == distances[src]:
            for dest in edges.get(src, dict()):
                for (dept, t) in edges[src].get(dest, set()):
                    b = blood if time <= dept else (blood + 1)
                    if (b, dept + t) < distances.get(dest, (b + 1, 0)):
                        distances[dest] = (b, dept + t)
                        q.put((b, dept + t, dest))

    print("Test Case %d." % test_number)
    if destination in distances:
        print("Vladimir needs %d litre(s) of blood." % distances[destination][0])
    else:
        print("There is no route Vladimir can take.")
