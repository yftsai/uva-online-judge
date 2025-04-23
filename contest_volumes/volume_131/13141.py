# #easy
from sys import stdin

branches = [(1, 0), (1, 0), (1, 0)]
for lv in range(3, 86):
    b = (branches[-1][1] // 2, branches[-1][0] * 2 + branches[-1][1])
    branches.append(b)

for line in stdin:
    n = int(line)
    if n == 0:
        break
    else:
        print(branches[n][0] + branches[n][1])
