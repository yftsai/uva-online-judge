# #sorting
from itertools import islice

def msort(data, i, j, buff):
    if i + 1 >= j:
        return (0, False)
    else:
        m = (i + j) // 2
        c, s = msort(data, i, m, buff)
        d, t = msort(data, m, j, buff)
        if s and not t:
            data[i:m] = islice(buff, i, m)
            data, buff = buff, data
            s = False
        elif not s and t:
            buff[i:m] = islice(data, i, m)
            s = True
        elif not s and not t:
            data, buff = buff, data

        k, o = m, i
        c += d
        while i < m or k < j:
            if i == m or (k < j and buff[k] < buff[i]):
                data[o] = buff[k]
                k += 1
                c += m - i
            else:
                data[o] = buff[i]
                i += 1
            o += 1

        return (c, not s)

try:
    data = [0] * 24
    buff = [0] * 24
    while True:
        n = int(input())
        starts = map(int, input().split())
        order = dict((next(starts), i) for i in range(n))

        ends = input().split()
        for i in range(n):
            data[i] = order[int(ends[i])]
        print(msort(data, 0, n, buff)[0])
except EOFError:
    pass
