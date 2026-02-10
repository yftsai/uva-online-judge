# #trivial
m, n = map(int, input().split())

points = {}
for _ in range(m):
    w, p = input().split()
    points[w] = int(p)

for _ in range(n):
    p = 0
    while True:
        line = input().strip()
        if line == '.':
            break
        else:
            for w in line.split():
                p += points.get(w, 0)
    print(p)
