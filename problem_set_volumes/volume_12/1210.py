# #easy
primes = [2]
for q in range(3, 10001, 2):
    if all(q % p > 0 for p in primes):
        primes.append(q)

while True:
    n = int(input())
    if n == 0:
        break
    else:
        count = 0
        length = 0
        sum = 0
        for start in range(len(primes)):
            if primes[start] > n:
                break
            else:
                while sum > n:
                    length -= 1
                    sum -= primes[start + length]
                while sum < n and start + length < len(primes):
                    sum += primes[start + length]
                    length += 1
                if sum == n:
                    count += 1
                sum -= primes[start]
                length -= 1
        print(count)
