# #trivial
from sys import stdin

n, prices = None, None

for line in stdin:
    line = line.strip()

    if line == "":
        pass
    elif n == None:
        n = int(line)
    elif prices == None:
        prices = sorted(map(int, line.split()))
    else:
        m = int(line)
        i, j, b = None, None, len(prices) - 1
        for a in range(len(prices)):
            while a < b and prices[a] + prices[b] > m:
                b -= 1
            if a < b and prices[a] + prices[b] == m:
                i, j = prices[a], prices[b]
        print("Peter should buy books whose prices are %d and %d." % (i, j))
        print()
        n, prices = None, None
