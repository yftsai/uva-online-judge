# #easy
from sys import stdin

def add(s, i):
    while i >= len(s):
        s.append('0')

    if s[i] == '0':
        if i+1 < len(s) and s[i+1] == '1':
            s[i+1] = '0'
            s = add(s, i+2)
        elif i == 0 or s[i-1] == '0':
            s[i] = '1'
        else:
            s[i-1] = '0'
            s = add(s, i+1)
    elif i == 0:
        s[0] = '0'
        s = add(s, 1)
    elif i == 1:
        s = add(add(s, 0), 0)
    else:
        s = add(add(s, i-1), i-2)

    return s

first_test = True
while True:
    s, a = stdin.readline().strip(), stdin.readline().strip()
    if len(s) == 0:
        break
    else:
        stdin.readline()

    s = list(reversed(s))
    for i in range(0, len(a)):
        if a[i] == '1':
            s = add(s, len(a)-1-i)

    if first_test:
        first_test = False
    else:
        print()
    print("".join(reversed(s)))
