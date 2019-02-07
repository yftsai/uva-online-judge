# #easy
while True:
    h, m = map(int, input().split(":"))
    if h == 0:
        break
    else:
        ah = 360 / 12 * ((0 if h == 12 else h) + m / 60)
        am = 360 / 60 * m
        a = (am - ah) if am > ah else (ah - am)
        a = a if a <= 180 else (360 - a)

        print("%.3f" % a)
