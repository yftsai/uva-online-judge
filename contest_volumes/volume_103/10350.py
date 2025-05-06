# #easy #dynamic_programming
try:
    while True:
        print(input())
        n, m = map(int, input().split())
        times = [0] * m
        ts = [None] * m
        for _ in range(n - 1):
            holes = map(int, input().split())
            for i in range(m):
                ts[i] = times[0] + 2 + next(holes)
            for i in range(1, m):
                holes = map(int, input().split())
                for j in range(m):
                    ts[j] = min(times[i] + 2 + next(holes), ts[j])
            times, ts = ts, times
        print(min(times))

except:
    pass
