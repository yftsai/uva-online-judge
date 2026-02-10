# #prime_number
def reverse_to_numbers(primes, i, factors, n, numbers):
    if i >= len(primes):
        return

    reverse_to_numbers(primes, i + 1, factors, n, numbers)

    v = 1
    fs = list(factors)
    s = sum(factors)
    while True:
        v *= primes[i]
        t = [f * v for f in factors]
        fs.extend(t)
        s += sum(t)
        if s > 1000:
            break
        else:
            m = n * v
            numbers[s] = max(m, numbers.get(s, -1))
            reverse_to_numbers(primes, i + 1, fs, m, numbers)

primes = [2]
for n in range(3, 1001):
    if all(map(lambda p: n % p != 0, primes)):
        primes.append(n)

numbers = { 1: 1 }
reverse_to_numbers(primes, 0, [1], 1, numbers)

cno = 1
n = 1
while True:
    n = int(input())
    if n == 0:
        break
    else:
        print("Case %d: %d" % (cno, numbers.get(n, -1)))
        cno += 1
