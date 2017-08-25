# #trivial
for t in range(int(input())):
    _ = int(input())
    durations = map(int, input().split())
    costs = (0, 0)
    for d in durations:
        costs = (costs[0] + (d //30 +1) *10, costs[1] + (d //60 +1) *15)
    if costs[0] < costs[1]:
        print("Case %d: Mile %d" % (t +1, costs[0]))
    elif costs[0] == costs[1]:
        print("Case %d: Mile Juice %d" % (t +1, costs[0]))
    else:
        print("Case %d: Juice %d" % (t +1, costs[1]))
