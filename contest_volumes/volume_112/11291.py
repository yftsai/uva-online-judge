# #parsing #easy
def parse(formula, i = 0):
    j = next(j for j in range(i, len(formula)) if formula[j] != ' ')
    if formula[j] == '(':
        i, j = j + 1, formula.find(' ', j + 1)
        p = float(formula[i: j])
        e1, i = parse(formula, j + 1)
        e2, i = parse(formula, i)
        i = formula.find(')', i) + 1
        return (p, e1, e2), i
    else:
        i, j = j, next((k for k in range(j, len(formula)) if not formula[k] in "-0123456789"), len(formula))
        return int(formula[i: j]), j

def evaluate(exp):
    if isinstance(exp, int):
        return exp
    else:
        p, e1, e2 = exp
        x = evaluate(e1)
        y = evaluate(e2)
        return p * (x + y) + (1 - p) * (x - y)

while True:
    formula = input()
    if formula == "()":
        break
    else:
        exp, _ = parse(formula)
        print("%.2f" % evaluate(exp))
