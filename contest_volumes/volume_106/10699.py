# #easy
is_prime = [True] * 1001
primes = [2]
for p in range(3, len(is_prime), 2):
    if is_prime[p]:
        primes.append(p)
        for q in range(p * p, len(is_prime), p):
            is_prime[q] = False

while True:
    n = int(input())
    if n == 0:
        break
    else:
        count, m = 0, n
        for p in primes:
            if m % p == 0:
                count += 1
                while m % p == 0:
                    m //= p
        count += 0 if m == 1 else 1
        print(n, ":", count)
