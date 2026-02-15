# #shortest_path
s, p = map(int, input().split())

indexes = {}
planets = {}
routes = [ [None] * s for _ in range(s) ]

for _ in range(p):
    ei, ej, dij = input().split()

    if ei not in indexes:
        i = len(indexes)
        indexes[ei] = i
        planets[i] = ei
    else:
        i = indexes[ei]

    if ej not in indexes:
        j = len(indexes)
        indexes[ej] = j
        planets[j] = ej
    else:
        j = indexes[ej]

    dij = int(dij)
    routes[i][j] = (dij, 0, None)
    routes[j][i] = (dij, 0, None)

for k in range(s):
    for i in range(s):
        for j in range(s):
            if routes[i][k] == None or routes[k][j] == None:
                d = None
                m = None
            else:
                d = routes[i][k][0] + routes[k][j][0]
                m = routes[i][k][1] + routes[k][j][1] + 1

            r = routes[i][j]
            if d != None and (r == None or d < r[0] or (d == r[0] and m < r[1])):
                routes[i][j] = (d, m, k)

for _ in range(int(input())):
    ek, em = input().split()
    k = indexes[ek]
    m = indexes[em]

    route = []
    stack = [(k, m)]
    while len(stack) > 0:
        e, f = stack[-1]
        stack.pop()
        r = routes[e][f]
        if r[1] == 0:
            route.append(planets[e])
        else:
            n = r[2]
            stack.append((n, f))
            stack.append((e, n))
    route.append(em)

    print(" ".join(map(str, route)))
