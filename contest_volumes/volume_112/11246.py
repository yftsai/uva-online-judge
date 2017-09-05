# #arithmetic
for _ in range(int(input())):
    n, k = map(int, input().split())
    size = n
    b, s = k, -1
    while b <= n:
        size += s * (n //b)
        b, s = b * k, s * (-1)
    print(size)
