# #dynamic_programming
for _ in range(int(input())):
    a = input()
    b = input()

    if len(a) > len(b):
        a, b = b, a

    rows = [ list(range(0, len(a) + 1)), [0] * (len(a) + 1) ]
    for c in b:
        rows[1][0] = rows[0][0] + 1
        for i in range(len(a)):
            if c == a[i]:
                rows[1][i + 1] = rows[0][i]
            else:
                rows[1][i + 1] = min(rows[0][i], rows[0][i + 1], rows[1][i]) + 1
        rows[0], rows[1] = rows[1], rows[0]

    print(rows[0][-1])
