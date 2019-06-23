# #trivial
def gcd(a, b):
    while a % b != 0:
        a %= b
        a, b = b, a
    return b

for _ in range(int(input())):
    p, _, q = input().split()
    p, q = int(p), int(q)
    d = gcd(p, q)
    print(p // d, '/', q // d)
