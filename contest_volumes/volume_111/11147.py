# #binary_tree

# build() returns a BST from `ms[b:e]`
# `ms` is a list of (number, count, sum) to simplify choosing a root in a list
# with duplicated values.
def build(ms, b, e):
    if b >= e:
        return None

    # binary search
    # If the root candidate changes from a negative value to a positive value,
    # both the sum of the left subtree and right subtree may decrease. Thus,
    # the implementation handles negative and non-negative values separately.
    q0 = [(b, e)]
    q1 = []
    while len(q0) > 0:
        lo, up = q0[-1]
        q0.pop()

        if lo + 2 >= up:
            q1.append((lo, up))
        elif (ms[lo][0] >= 0) != (ms[up - 1][0] >= 0):
            m = (lo + up) // 2
            if (ms[lo][0] >= 0) == (ms[m][0] >= 0):
                m += 1
            q0.append((lo, m))
            q0.append((m, up))
        else:
            m = (lo + up) // 2
            lsum = ms[m][2] - (ms[b - 1][2] if b > 0 else 0) - ms[m][0]
            rsum = ms[e - 1][2] - ms[m][2]

            if (ms[m][0] >= 0 and lsum < rsum) or (ms[m][0] < 0 and lsum > rsum):
                q0.append((m, up))
            else:
                q0.append((lo, m + 1))

    # linear search
    diff = None
    for (lo, up) in q1:
        for i in range(lo, up):
            ls = ms[i][2] - (ms[b - 1][2] if b > 0 else 0) - ms[i][0]
            d = abs(ls - ms[e - 1][2] + ms[i][2])
            if diff is None or d < diff or (d == diff and ls > lsum):
                root = i
                lsum = ls
                diff = d

    t = ms[root]
    s = (t[0], t[1] - 1, t[2] - t[0])
    ms[root] = s
    lt = build(ms, b, root if ms[root][1] == 0 else root + 1)
    ms[root] = t
    return (ms[root][0], lt, build(ms, root + 1, e))

def format(t):
    if t[1] is None and t[2] is None:
        return str(t[0])
    elif t[1] is None:
        return str(t[0]) + '(' + format(t[2]) + ')'
    elif t[2] is None:
        return str(t[0]) + '(' + format(t[1]) + ')'
    else:
        return str(t[0]) + '(' + format(t[1]) + ',' + format(t[2]) + ')'

for cn in range(1, int(input()) + 1):
    n = int(input())
    ns = sorted(map(int, input().split()))

    ms = [(ns[0], 0, 0)]    # (number, count, sum)
    for num in ns:
        if num == ms[-1][0]:
            t = ms[-1]
            ms[-1] = (t[0], t[1] + 1, t[2] + num)
        else:
            ms.append((num, 1, ms[-1][2] + num))

    t = build(ms, 0, len(ms))
    print("Case #%d: %s" % (cn, format(t)))
