# #dynamic_programming
from sys import stdin

turtles = []
for line in stdin:
    weight, strength = map(int, line.split())
    turtles.append((strength, weight))
turtles = sorted(turtles, reverse = True)

capacities = [ sum([ t[1] for t in turtles ]) ]
for t in turtles:
    for h in range(len(capacities)-1, -1, -1):
        if capacities[h] >= t[1]:
            c = min(capacities[h] - t[1], t[0] - t[1])
            if h+1 == len(capacities):
                capacities.append(c)
            elif capacities[h+1] < c:
                capacities[h+1] = c

print(len(capacities)-1)
