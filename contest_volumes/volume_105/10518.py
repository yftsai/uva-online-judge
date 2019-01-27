# #matrix
case_number = 1

def multiply(m, n, b):
    r = []
    for i in range(len(m)):
        s = []
        for j in range(len(n[0])):
            s.append(sum(m[i][k] * n[k][j] for k in range(len(m[i]))) % b)
        r.append(s)
    return r

def power(m, e, b):
    r = [ [1, 0], [0, 1] ]
    s = m
    while e > 0:
        if e % 2 == 1:
            r = multiply(r, s, b)
        e >>= 1
        s = multiply(s, s, b)
    return r

while True:
    n, b = map(int, input().split())
    if b == 0:
        break
    else:
        fibs = [ [0, 1] ]
        if b == 1:
            r = 0
        elif n <= 1:
            r = 1
        else:
            c = multiply([ [1, 1] ], power([ [0, 1], [1, 1] ], n - 1, b), b)
            d = multiply([ [0, 1] ], power([ [0, 1], [1, 1] ], n - 1, b), b)
            r = (c[0][1] + d[0][0] + d[0][1] - 1 + b) % b

        print("Case %d: %d %d %d" % (case_number, n, b, r))
        case_number += 1
