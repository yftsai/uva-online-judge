# #easy
for cno in range(1, int(input()) + 1):
    players = []
    for i in range(10):
        name, a, d = input().split()
        players.append((-int(a), int(d), name))
    players.sort()
    attackers = sorted(players[i][2]     for i in range(5))
    defenders = sorted(players[5 + i][2] for i in range(5))
    print("Case %d:" % cno)
    print("(%s)" % ", ".join(attackers))
    print("(%s)" % ", ".join(defenders))
