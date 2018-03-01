# The solution pattern was mostly observed from the sample input.
from sys import stdin

for line in stdin:
    n = int(line)
    odds, evens = range(1, n + 1, 2), range(2, n + 1, 2)

    if n == 2 or n == 3:
        config = None
    elif n % 6 == 2:
        config = list(evens[1:]) + list(evens[:1]) + list(odds[3:]) + list(odds[:3])
    elif n % 6 == 3:
        config = list(evens[1:]) + list(evens[:1]) + list(odds[2:]) + list(odds[:2])
    else:
        config = list(evens) + list(odds)

    print("Impossible" if config == None else " ".join(map(str, config)))
