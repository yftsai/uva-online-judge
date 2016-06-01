# #easy
from sys import stdin

ntree = {
    0: 1,
    1: 1
}

while True:
    nnode = len(ntree)
    ntree[nnode] = 0
    for l in range(0, nnode):
        ntree[nnode] += ntree[l] * ntree[nnode-l-1]
    if ntree[nnode]>2**32-1:
        break
del ntree[0]    # only rooted trees are considered

nnode = { t: n for n, t in ntree.items() }

for n in stdin:
    print(nnode[int(n)])
