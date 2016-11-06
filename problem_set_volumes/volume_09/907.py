from sys import stdin
import itertools

def plan(n, k, ds):
    maxdis = sum(ds)
    mindis = max(maxdis // (k+1), max(ds))

    for i in range(0, len(ds)):
        acc = 0
        for j in range(i, len(ds)):
            acc += ds[j]

            if acc < mindis:
                continue
            if acc >= maxdis:
                break

            d, night = 0, 0
            for l in range(0, len(ds)):
                if d + ds[l] <= acc:
                    d += ds[l]
                else:
                    d = ds[l]
                    night += 1

            maxdis = acc if night <= k else maxdis
    return maxdis

n, k, d = None, None, []
for line in stdin:
    if n is None:
        n, k = map(int, line.split())
    elif len(d) < n:
        d.append(int(line))
    else:
        d.append(int(line))
        print(plan(n, k, d))
        n, k, d = None, None, []    # reset
