# #longest_increasing_subsequence
from bisect import bisect

for case_number in range(1, int(input()) + 1):
    n, p, q = map(int, input().split())
    xindexes = dict()
    for x in map(int, input().split()):
        xindexes[x] = len(xindexes)

    subsequences = []
    for y in map(int, input().split()):
        if y in xindexes:
            i = xindexes[y]
            j = bisect(subsequences, xindexes[y])
            if j == len(subsequences):
                subsequences.append(i)
            else:
                subsequences[j] = i

    print("Case %d: %d" % (case_number, len(subsequences)))
