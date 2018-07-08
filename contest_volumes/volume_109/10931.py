# #trivial
from sys import stdin

for line in stdin:
    i = int(line)
    if i == 0:
        break
    else:
        b = "{0:b}".format(i)
        p = sum(1 for c in b if c == '1')
        print("The parity of %s is %d (mod 2)." % (b, p))
