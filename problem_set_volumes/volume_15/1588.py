# #easy
def fit_order(lm, ld):
    d = lm - ld
    for i in range(d + 1):
        yield i
    for i in range(ld):
        yield d + 1 + i
        yield -1 - i

try:
    while True:
        secm = input()
        secd = input()
        if len(secm) < len(secd):
            secm, secd = secd, secm

        teeth = []
        for i in range(len(secd)):
            if secd[i] == '2':
                teeth.append(i)

        fit = lambda shift: all(0 > shift + i or shift + i >= len(secm) or secm[shift + i] == '1' for i in teeth)
        shift = next(i for i in fit_order(len(secm), len(secd)) if fit(i))

        print(max(len(secm), -shift + len(secm) if shift < 0 else shift + len(secd)))

except:
    pass
