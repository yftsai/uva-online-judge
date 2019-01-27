# #easy
coeffs = [[1, 1]]
for i in range(1, 50):
    coeffs.append([1] + [coeffs[i - 1][j] + coeffs[i - 1][j + 1] for j in range(i)] + [1])

for case_number in range(1, int(input()) + 1):
    formula = input()
    i = formula.find('(') + 1
    j = formula.find('+', i)
    a, i = formula[i: j], j + 1
    j = formula.find(')', i)
    b, i = formula[i: j], formula.find('^', j + 1) + 1
    k = int(formula[i:])

    formula = ""
    for bexp in range(len(coeffs[k - 1])):
        formula += "" if bexp == 0 else "+"
        c = coeffs[k - 1][bexp]
        formula += "" if c == 1 else "%d*" % c
        aexp = k - bexp
        formula += "" if aexp == 0 else (a + ("" if aexp == 1 else "^%d" % aexp))
        formula += "" if aexp == 0 or bexp == 0 else "*"
        formula += "" if bexp == 0 else (b + ("" if bexp == 1 else "^%d" % bexp))
    print("Case %d: %s" % (case_number, formula))
