# #easy
from collections import deque

n = int(input())

for _ in range(n):
    n, s, q = map(int, input().split())
    qs = []
    for _ in range(n):
        qs.append(deque())
        for cargo in map(int, input().split()[1:]):
            qs[-1].append(cargo - 1)

    time = 0
    station = 0
    carrier = []
    leftover = sum(map(len, qs))
    while leftover > 0:
        leftover -= len(carrier) + len(qs[station])
        while len(carrier) > 0 and (carrier[-1] == station or len(qs[station]) < q):
            time += 1
            if carrier[-1] != station:
                qs[station].append(carrier[-1])
            carrier.pop()
        while len(carrier) < s and len(qs[station]) > 0:
            time += 1
            carrier.append(qs[station][0])
            qs[station].popleft()

        leftover += len(carrier) + len(qs[station])
        if leftover > 0:
            station = (station + 1) % n
            time += 2

    print(time)
