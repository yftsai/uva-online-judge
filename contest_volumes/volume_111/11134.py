# #divide_and_conquer
from queue import PriorityQueue

def assign(rs):
    rs = sorted(rs, key = lambda r: r[0])
    q = PriorityQueue()
    ps = []
    r = 0
    for p in range(1, len(rs) + 1):
        while r < len(rs) and rs[r][0] <= p:
            q.put((rs[r][1], rs[r][2]))
            r += 1
        if q.empty():
            break
        else:
            e = q.get()
            if e[0] < p:
                break
            else:
                ps.append((e[1], p))
    return sorted(ps)

while True:
    n = int(input())
    if n == 0:
        break
    else:
        rs = [ list(map(int, input().split())) for i in range(n)]
        xs = assign([(rs[i][0], rs[i][2], i) for i in range(n)])
        ys = assign([(rs[i][1], rs[i][3], i) for i in range(n)]) if len(xs) == n else []

        if len(xs) < n or len(ys) < n:
            print('IMPOSSIBLE')
        else:
            xs = sorted(xs)
            ys = sorted(ys)
            for i in range(n):
                print(xs[i][1], ys[i][1])
