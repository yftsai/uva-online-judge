# #trivial
for _ in range(int(input())):
    g, l = map(int, input().split())
    if l % g == 0:
        print(g, l)
    else:
        print(-1)
