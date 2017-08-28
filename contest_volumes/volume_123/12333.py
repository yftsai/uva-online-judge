t = int(input())
indexes = [-1] * t
prefixes = dict()
for i in range(t):
    f = int(input())
    if f == 1:
        indexes[i] = 0
    elif f > 1:
        prefixes[f] = prefixes.get(f, [])
        prefixes[f].append(i)

f, g = 1, 1
base, limit = 1, 10**41-1
for i in range(2, 10**5):
    h = f + g
    f, g = g, h

    k = h // base
    if k > limit:
        k //= 10
        base *= 10
    while k > 0:
        if k in prefixes:
            for j in prefixes[k]:
                indexes[j] = i
            del prefixes[k]
        k //= 10

for i in range(t):
    print("Case #%d: %d" % (i+1, indexes[i]))
