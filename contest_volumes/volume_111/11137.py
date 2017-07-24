# #dynamic_programming
from sys import stdin

coins = [ i**3 for i in range(2, 22) ]
way_counts = [1]* 10000
for cv in coins:
    for amount in range(len(way_counts) - 1, 0, -1):
        for v in range(cv, amount + 1, cv):
            way_counts[amount] += way_counts[amount - v]

for a in stdin:
    print(way_counts[int(a)])
