# #easy #arithmetic
for _ in range(int(input())):
    input()
    signs = input()
    n = int(input())

    ranges = [None for _ in signs]
    ranges[-1] = range(0, 2) if signs[-1] == 'p' else range(-1, 1)
    for exp in range(1, len(signs)):
        index = len(signs) - 1 - exp
        if signs[index] == 'p':
            ranges[index] = range(ranges[index + 1][0], ranges[index + 1][-1] + 1 + 2**exp)
        else:
            ranges[index] = range(ranges[index + 1][0] - 2**exp, ranges[index + 1][-1] + 1)

    if not n in ranges[0]:
        print('Impossible')
    else:
        rep = ""
        for i in range(len(signs) - 1):
            if n in ranges[i + 1]:
                rep += '0'
            else:
                rep += '1'
                n -= (1 if signs[i] == 'p' else -1) * 2**(len(signs) - 1 - i)
        rep += '0' if n == 0 else '1'
        print(rep)
