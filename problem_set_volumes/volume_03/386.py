# #trivial
icbrt = lambda x: round(x ** (1 / 3))

for a in range(3, 201):
    ac = a ** 3
    for b in range(2, icbrt(ac / 3) + 1):
        ccdc = ac - b ** 3
        for c in range(b, icbrt(ccdc / 2) + 1):
            dc = ccdc - c ** 3
            d = icbrt(dc)
            if c <= d and dc == d ** 3:
                print("Cube = %d, Triple = (%d,%d,%d)" % (a, b, c, d))
