# #easy
from sys import stdin

cno = 1
for line in stdin:
    n, m = line.split()
    ni, nf = n.split('.')
    mi, mf = m.split('.')

    ni, mi = int(ni), int(mi)
    if ni != mi:
        cmp = -1 if ni < mi else 1
    else:
        if len(nf) < len(mf):
            nf = nf.ljust(len(mf), '0')
        elif len(nf) > len(mf):
            mf = mf.ljust(len(nf), '0')
        nf, mf = int(nf), int(mf)

        if nf < mf:
            cmp = -1
        elif nf == mf:
            cmp = 0
        else:
            cmp = 1

    print("Case %d: %s" % (cno, ("Smaller", "Same", "Bigger")[cmp + 1]))
    cno += 1
