# #trivial
from sys import stdin

for line in stdin:
    line = line.split()
    if line[0] == '0':
        break
    else:
        g, s = int(line[0]), line[1]
        glen = len(s)//g
        line = [ s[i:i-glen:-1] for i in range(-len(s)-1+glen, 0, glen) ]
        print("".join(line))
