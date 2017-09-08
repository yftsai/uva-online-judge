# #breadth_first_search #easy
from math import sqrt
from queue import Queue

primes = [2]
for i in range(3, 10000, 2):
    f, r = None, int(sqrt(i))
    for p in primes:
        if i % p == 0:
            f = p
            break
        elif p > r:
            break
    if f == None:
        primes.append(i)
primes = list(filter(lambda n: n >= 1000, primes))

outs = [ [] for _ in range(len(primes))]
for i in range(len(primes)):
    for j in range(i + 1, len(primes)):
        p, q = primes[i], primes[j]
        while p % 10 == q % 10:
            p, q = p//10, q//10
        if p // 10 == q // 10:
            outs[i].append(j)
            outs[j].append(i)

for _ in range(int(input())):
    m, n = map(int, input().split())
    m = primes.index(m)
    n = primes.index(n)

    change_counts = [0 if i == m else None for i in range(len(primes))]
    q = Queue()
    q.put(m)
    while (not q.empty()) and change_counts[n] == None:
        i = q.get()
        for j in filter(lambda j: change_counts[j] == None, outs[i]):
            change_counts[j] = change_counts[i] + 1
            q.put(j)
    print('Impossible' if change_counts[n] == None else change_counts[n])
