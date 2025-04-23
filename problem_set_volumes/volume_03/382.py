# #easy
from sys import stdin

primes = [2]
for n in range(3, 60_000, 2):
    for p in primes:
        q = n // p
        r = n % p
        if r == 0:
            break
        if p >= q:
            break
    if r != 0:
        primes.append(n)

def get():
    for line in stdin:
        for n in map(int, line.split()):
            if n != 0:
                yield n

print('PERFECTION OUTPUT')
for n in get():
    ps = []
    es = []
    r = n
    for p in primes:
        e = 0
        while r % p == 0:
            r //= p
            e += 1
        if e > 0:
            ps.append(p)
            es.append(e)
        elif p >= r // p:
            break
    if r > 1:
        ps.append(r)
        es.append(1)

    fs = list(es)
    sum = 0
    while any(fs) and sum <= n:
        fs[0] -= 1
        for i in range(len(fs)):
            if fs[i] < 0:
                fs[i] = es[i]
                fs[i + 1] -= 1
            else:
                break

        f = 1
        for i in range(len(fs)):
            f *= ps[i] ** fs[i]
        sum += f

    print("%5d  %s" % (n, 'DEFICIENT' if sum < n else 'PERFECT' if n == sum else 'ABUNDANT'))

print('END OF OUTPUT')
