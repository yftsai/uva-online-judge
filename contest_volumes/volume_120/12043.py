# #easy #prime_number
from functools import reduce
from math import ceil, floor

def sum_divisors(factors):
    exps = [0] * len(factors)
    vals = [1] * len(factors)
    d = 1
    s = 0
    while True:
        s += d
        exps[0] += 1
        for i in range(len(factors)):
            if exps[i] <= factors[i][1]:
                d //= vals[i]
                vals[i] = factors[i][0] ** exps[i]
                d *= vals[i]
                break
            elif i + 1 < len(factors):
                d //= vals[i]
                exps[i + 1] += 1
                exps[i] = 0
                vals[i] = 1
        if exps[-1] > factors[-1][1]:
            break
    return s

primes = []
sqrte = 0
d = [ None, 1 ]
s = [ None, 1 ]

for n in range(2, 100_001):
    if sqrte < len(primes) and primes[sqrte] ** 2 <= n:
        sqrte += 1

    i = next((i for i in range(sqrte) if n % primes[i] == 0), None)
    if i is None:
        primes.append(n)
        d.append(2)
        s.append(n + 1)
    else:
        m = n
        factors = []
        for j in range(i, sqrte):
            if m == 1:
                break
            elif m % primes[j] == 0:
                e = 0
                while m % primes[j] == 0:
                    m //= primes[j]
                    e += 1
                factors.append((primes[j], e))
        if m > 1:
            factors.append((m, 1))

        d.append(reduce(lambda acc, e: acc * (e + 1), (e for _, e in factors), 1))
        s.append(sum_divisors(factors))

for _ in range(int(input())):
    a, b, k = map(int, input().split())
    g = 0
    h = 0
    for i in range(ceil(a / k) * k, floor(b / k) * k + 1, k):
        g += d[i]
        h += s[i]
    print(g, h)
