# #dynamic_programming

def parenthesize(ms, index, length):
    if length == 1:
        return "A%d" % (index + 1)
    else:
        i = ms[index][length - 1][1]
        return "(%s x %s)" % (parenthesize(ms, index, i), parenthesize(ms, index + i, length - i))

case_number = 1

while True:
    n = int(input())
    if n == 0:
        break
    else:
        ds = []
        for _ in range(n):
            ds.append(tuple(map(int, input().split())))

        ms = [ [ None ] * (n - i) for i in range(n)]
        for i in range(n):
            ms[i][0] = (0, 1)
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j, c = None, None
                for k in range(1, length):
                    d = ms[i][k - 1][0] + ms[i + k][length - k - 1][0] + ds[i][0] * ds[i + k][0] * ds[i + length - 1][1]
                    if j == None or d < c:
                        j, c = k, d
                ms[i][length - 1] = (c, j)

        print("Case %d: %s" % (case_number, parenthesize(ms, 0, n)))
        case_number += 1
