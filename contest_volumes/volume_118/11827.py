# #trivial
def gcd(a, b):
    while a % b != 0:
        a, b = b, a % b
    return b

for _ in range(int(input())):
    vals = list(map(int, input().split()))
    m = len(vals)
    print(max(gcd(vals[i], vals[j]) for i in range(m) for j in range(i + 1, m)))
