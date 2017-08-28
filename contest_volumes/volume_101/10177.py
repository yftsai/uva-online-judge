# #trivial
from sys import stdin

for line in stdin:
    n = int(line)
    s2, s3, s4 = 0, 0, 0
    for i in range(1, n+1):
        s2 += i**2
        s3 += i**3
        s4 += i**4
    r2 = ((n + 1) *n //2)**2 - s2
    r3 = ((n + 1) *n //2)**3 - s3
    r4 = ((n + 1) *n //2)**4 - s4
    
    print(s2, r2, s3, r3, s4, r4)
