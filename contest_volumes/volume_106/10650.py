# #prime_number
from bisect import bisect_left

primes = [2]
for n in range(3, 32000):
    if all(map(lambda p: n % p != 0, primes)):
        primes.append(n)

dprimes = []
i = 0
while i < len(primes) - 2:
    d = primes[i + 1] - primes[i]
    e = next(k for k in range(i + 2, len(primes)) if primes[k] - primes[k - 1] != d)
    if i + 2 < e:
        dprimes.append((primes[i], d, e - i - 1))
        i = e - 1
    else:
        i += 1

while True:
    x, y = map(int, input().split())
    if x == 0 and y == 0:
        break
    if x > y:
        x, y = y, x

    i = bisect_left(dprimes, (x, 0, 0))
    for i in range(bisect_left(dprimes, (x, 0, 0)), len(dprimes)):
        p, d, n = dprimes[i]
        if x > p or p >= y:
            break
        elif p + d * n <= y:
            print(" ".join(map(str, range(p, p + d * n + 1, d))))
