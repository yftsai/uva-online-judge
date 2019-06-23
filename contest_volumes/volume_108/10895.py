# #trivial
try:
    while True:
        m, n = map(int, input().split())
        tm = dict()
        for i in range(1, m + 1):
            col_indexes = map(int, input().split())
            next(col_indexes)
            vals = map(int, input().split())
            for j, v in zip(col_indexes, vals):
                if not (j in tm):
                    tm[j] = [(i, v)]
                else:
                    tm[j].append((i, v))

        print(n, m)
        for i in range(1, n + 1):
            if not i in tm:
                print(0)
                print()
            else:
                tm[i].sort()
                print(len(tm[i]), end = '')
                print(''.join((" %d" % j) for j, _ in tm[i]))
                print(' '.join(map(str, (v for _, v in tm[i]))))
except:
    pass
