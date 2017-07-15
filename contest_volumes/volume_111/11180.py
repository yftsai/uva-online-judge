# #easy
u = 1j-1
for t in range(1, int(input())+1):
    a, b = map(int, input().split())
    n = a + b*(1j)

    rep, base = 0, 1
    while n != 0:
        # the result of a floor division guarantees either 0 or 1
        if int(n.real)%2 == int(n.imag)%2:
            n = n/u
        else:
            rep += base
            n = (n - 1)/u
        base *= 10

    print("Case #%d: %d" % (t, rep))
