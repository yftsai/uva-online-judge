# #trivial

for cno in range(1, int(input()) + 1):
    input()

    hjump = 0
    ljump = 0
    walls = map(int, input().split())
    wall = next(walls)
    for w in walls:
        if wall < w:
            hjump += 1
            wall = w
        elif wall > w:
            ljump += 1
            wall = w

    print("Case %d: %d %d" % (cno, hjump, ljump))
