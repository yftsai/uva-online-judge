# #greedy
# The problem can also be solved with dynamic programming in O(n^2).
for t in range(1, int(input())+1):
    n, d = map(int, input().split())
    parse = lambda s: (lambda p: (int(p[1]), p[0]))(s.split('-'))
    stones = [(0, 'B')] + sorted(list(map(parse, input().split()))) + [(d, 'B')]

    max_leap = 0
    for init_leap in range(1, 3):
        pos = 0
        while pos < len(stones) - 1:
            if stones[pos+1][1] == 'B':
                max_leap = max(max_leap, stones[pos + 1][0] - stones[pos][0])
                pos += 1
            elif stones[pos][1] == 'B':
                max_leap = max(max_leap, stones[pos + init_leap][0] - stones[pos][0])
                pos += init_leap
            else:
                max_leap = max(max_leap, stones[pos + 2][0] - stones[pos][0])
                pos = pos + 2
    print("Case %d: %d" % (t, max_leap))
