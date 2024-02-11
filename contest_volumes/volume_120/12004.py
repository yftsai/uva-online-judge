# easy

for casen in (range(1, int(input()) + 1)):
    n = int(input())
    p = (n - 1) * n // 2
    if p % 2 == 0:
        print("Case %d: %d"   % (casen, p / 2))
    else:
        print("Case %d: %d/2" % (casen, p))
