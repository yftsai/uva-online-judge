# #derangement #combinatorics
from sys import stdin

ds = [1, 0]
for j in range(2, 21):
    ds.append((j - 1) * (ds[j - 2] + ds[j - 1]))

for line in stdin:
    n, m = map(int, line.split())
    count, c = ds[n], 1
    for i in range(1, m + 1):
        c = c * (n - i + 1) //i
        count += c * ds[n - i]
    print(count)
