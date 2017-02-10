# #combinatorics
from math import factorial
from sys import stdin

# When there are n people, there are perm_count[n, m] permutations where m people have unblocked vision to one end.
perm_count = {(0, 0): 1}
for n in range(1, 14):
    # the highest person always has unblocked vision, so m >= 1
    for m in range(1, n+1):
        perm_count[n, m] = 0
        # let the highest person at i-th position
        for i in range(0, n):
            perm_count[n, m] += factorial(n-1) //factorial(i) * perm_count.get((i, m-1), 0)

for _ in range(0, int(stdin.readline())):
    line = stdin.readline()
    n, p, r = map(int, line.split())
    count = 0
    # let the highest person at i-th position
    for i in range(p-1, n-r+1):
        c = factorial(n-1) //factorial(i) //factorial(n-1-i)
        count += c * perm_count.get((i, p-1), 0) * perm_count.get((n-i-1, r-1), 0)
    print(count)
