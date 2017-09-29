# #easy
for _ in range(int(input())):
    n, p, i = input().split()
    n, p, i = int(n), float(p), int(i)
    q = 0 if p == 0 else (1 - p) **(i - 1) * p / (1 - (1 - p) **n)
    print("%.4f" % q)
