# #easy
from sys import stdin

counts = [1]
for n in range(1, 11):
    counts.append(0)
    for m in range(0, 2 * n - 1, 2):
        counts[n] += counts[m // 2] * counts[n - 1 - m // 2]

is_first = True
for line in stdin:
    try:
        n = int(line)
        if is_first:
            is_first = False
        else:
            print()
        print(counts[n])
    except ValueError:
        pass

