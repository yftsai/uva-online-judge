# #trivial
to_mm = lambda m: m * 1000

try:
    while True:
        ngd = input().split()
        n = int(ngd[0])
        gx, gy, dx, dy = map(round, map(to_mm, map(float, ngd[1:])))

        ex, ey = None, None
        for _ in range(n):
            xy = input()
            if ex is None:
                x, y = map(round, map(to_mm, map(float, xy.split())))
                gd = (gx - x) ** 2 + (gy - y) ** 2
                dd = (dx - x) ** 2 + (dy - y) ** 2
                if gd * 4 <= dd:
                    ex, ey = x, y

        if ex is None:
            print('The gopher cannot escape.')
        else:
            print("The gopher can escape through the hole at (%.3f,%.3f)." % (ex / 1000, ey / 1000))

        input()
except:
    pass
