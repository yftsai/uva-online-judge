# #topological_sort #easy
while True:
    n, m = map(int, input().split())
    if n == 0:
        break
    else:
        s = set(range(1, n + 1))
        precedent_counts = [0] * n
        dependents = dict()
        for _ in range(m):
            i, j = map(int, input().split())
            if j in s:
                s.remove(j)
            if not i in dependents:
                dependents[i] = []
            dependents[i].append(j)
            precedent_counts[j - 1] += 1

        order = []
        while len(s) > 0:
            t = set()
            for i in s:
                order.append(i)
                if i in dependents:
                    for j in dependents[i]:
                        precedent_counts[j - 1] -= 1
                        if precedent_counts[j - 1] == 0:
                            t.add(j)
            s = t
        print(" ".join(map(str, order)))
