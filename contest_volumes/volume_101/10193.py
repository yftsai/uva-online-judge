# #easy #arithmetic
def gcd(m, n):
    while m % n > 0:
        m, n = n, m % n
    return n

for pair_number in range(1, int(input()) + 1):
    s1 = int(input(), 2)
    s2 = int(input(), 2)
    if gcd(s1, s2) > 1:
        print("Pair #%d: All you need is love!" % pair_number)
    else:
        print("Pair #%d: Love is not all you need!" % pair_number)
