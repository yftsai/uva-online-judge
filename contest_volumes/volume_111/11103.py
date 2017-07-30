# #easy
while True:
    line = input()
    if line == '0':
        break
    else:
        exprs, uops, bops = [], 0, []   # expressions, unary operators, binary operators
        for c in line:
            if c in "pqrst":
                exprs.append(c)
            elif c == 'N':
                uops += 1
            elif c in "KACE":
                bops.append(c)

        if len(exprs) > 0:
            exprs[-1] = "N"*uops + exprs[-1]
        while len(exprs) >= 2 and len(bops) > 0:
            exprs[-2] = bops[-1] + exprs[-2] + exprs[-1]
            exprs.pop()
            bops.pop()

        print(exprs[-1] if len(exprs) > 0 else "no WFF possible")
