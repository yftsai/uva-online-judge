# #trivial
# D is a relative distance, so the initial speed S doesn't matter.

n = int(input())

for _ in range(n):
    t, _, d = map(int, input().split())
    m = int(abs(d) * 1000 * 1000 / t / 24 / 60 / 60)
    print("%s %d tons" % ('Remove' if d > 0 and m > 0 else 'Add', m))
