# #easy
from sys import stdin
from math import sqrt

prime = [2]

def isprime(n):
    limit = int(sqrt(n))
    for p in prime:
        if p > limit:
            break
        elif n%p==0:
            return False
    return True

for i in range(3, 10**3, 2):
    if isprime(i):
        prime.append(i)

for n in stdin:
    r = int(n[::-1])
    n = int(n)
    if not isprime(n):
        print(n, "is not prime.")
    elif n == r or not isprime(r):
        print(n, "is prime.")
    else:
        print(n, "is emirp.")
