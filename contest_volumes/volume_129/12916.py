import math

primes = [2]
for n in range(3, 1000, 2):
    if all(n % p != 0 for p in primes):
        primes.append(n)

for _ in range(int(input())):
    line = input()

    counts = {}
    for c in line:
        counts[c] = counts.get(c, 0) + 1
    n = len(line)
    d = n
    for v in counts.values():
        d = math.gcd(v, d)

    facs = []
    exps = []
    for p in primes:
        if d % p == 0:
            facs.append(p)
            exps.append(0)
            while d % p == 0:
                exps[-1] += 1
                d //= p

    es = list(exps)
    while any(e > 0 for e in es):
        e = 1
        for i in range(len(es)):
            e *= facs[i] ** es[i]

        sz = len(line) // e
        s = line[:sz]
        if all(s == line[i:(i + sz)] for i in range(sz, n, sz)):
            d = max(e, d)

        j = next(j for j in range(len(es)) if es[j] > 0)
        for i in range(j):
            es[i] = exps[i]
        es[j] -= 1

    print(len(line) // d)
