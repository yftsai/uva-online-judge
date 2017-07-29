for t in range(int(input())):
    vals = sorted(list(map(int, input().split()))[1:])

    sum, perm = 0, [ vals[-1] ]
    i, j = 0, len(vals)-2
    while i < j:
        if perm[0] > vals[i]:
            sum += perm[0] + perm[-1] - vals[i] - vals[i+1]
            perm = [vals[i]] + perm + [vals[i+1]]
            i += 2
        else:
            sum += vals[j] + vals[j-1] - perm[0] - perm[-1]
            perm = [vals[j]] + perm + [vals[j-1]]
            j -= 2
        perm = (perm[0:2] + perm[len(perm)-2:]) if len(perm) > 4 else perm
    if i == j:
        if perm[0] > vals[i]:
            sum += perm[0] - vals[i]
        else:
            sum += vals[j] - perm[0]
    elif len(perm) >= 2 and abs(perm[0] - perm[-1]) > abs(perm[0] - perm[1]):
        sum += abs(perm[0] - perm[-1]) - abs(perm[0] - perm[1])
    elif len(perm) >= 2 and abs(perm[0] - perm[-1]) > abs(perm[-1] - perm[-2]):
        sum += abs(perm[0] - perm[-1]) - abs(perm[-1] - perm[-2])

    print("Case %d: %d" % (t + 1, sum))
