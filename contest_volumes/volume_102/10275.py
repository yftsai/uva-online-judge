def checksum(v):
    while v >= 100:
        v = v//100 + v%100
    return v

def multiply(x, y):
    sig = x[0]*y[0]     # significand
    exp = x[1]+y[1]     # exponent
    while sig>=10:
        sig /= 10
        exp += 1
    return [ sig, exp, checksum(x[2]*y[2]) ]

def bbpower(x):
    acc = [1, 0, 1]
    b = multiply([x, 0, x], acc)
    p = x
    while p>0:
        if p%2 == 1:
            acc = multiply(acc, b)
        p //= 2
        b = multiply(b, b)
    return acc

t = int(input())
for _ in range(0, t):
    s = input()
    nd_s = len(s)

    s = s[::-1]
    cs_s = 0
    for i in range(0, len(s), 2):
        cs_s = checksum(cs_s + int(s[i:i+2][::-1]))

    l = 1 if s == "1" else 2        # only 1^1 and 2^2 have the same number of digits
    r = 2 if s == "1" else 10**5    # exclusive upper bound, len(str(100000**100000)) == 500001
    while l<r:
        m = (l+r)//2
        bbp_m = bbpower(m)
        if bbp_m[1]+1 == nd_s:
            break
        elif nd_s < bbp_m[1]+1:
            r = m
        else:
            l = m + 1

    if l<r and bbp_m[2]==cs_s:
        print(m)
    else:
        print(-1)
