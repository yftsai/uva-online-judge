# #parsing #easy
from sys import stdin

vars = "pqrst"

def evaluate(assignment, line, start = 0):
    if vars.find(line[start]) != -1:
        return ((assignment >> vars.find(line[start])) % 2 == 1, start + 1)
    elif line[start] == 'N':
        v, end = evaluate(assignment, line, start + 1)
        return (not v, end)
    else:
        b1, mid = evaluate(assignment, line, start + 1)
        b2, end = evaluate(assignment, line, mid)
        if line[start] == 'K':
            return (b1 and b2, end)
        elif line[start] == 'A':
            return (b1 or b2, end)
        elif line[start] == 'C':
            return (not b1 or b2, end)
        else:
            return (b1 == b2, end)

for line in stdin:
    if line[0] == '0':
        break
    else:
        is_tautology = all(evaluate(assignment, line)[0] for assignment in range(0, 2**len(vars)))
        print("tautology" if is_tautology else "not")
