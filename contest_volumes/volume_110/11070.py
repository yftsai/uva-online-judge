# #stack
from sys import stdin

def get_operand(exp, i):
    j = i + 1
    while j < len(exp) and ('0' <= exp[j] <= '9' or exp[j] == '.'):
        j += 1
    return float(exp[i:j]), j

def operate(opds, opr):
    if opr == '+':
        opds[-2] = opds[-2] + opds[-1]
    else:
        opds[-2] = opds[-2] - opds[-1]
    opds.pop()

for exp in stdin:
    exp = exp.strip()

    opds = []
    opr = None

    opd, i = get_operand(exp, 0)
    opds.append(opd)

    while i < len(exp):
        o = exp[i]
        i += 1
        opd, i = get_operand(exp, i)

        if o == '*':
            opds[-1] = opds[-1] * opd
        elif o == '/':
            opds[-1] = opds[-1] / opd
        elif opr == None:
            opds.append(opd)
            opr = o
        else:
            operate(opds, opr)
            opds.append(opd)
            opr = o

    if opr != None:
        operate(opds, opr)
    print('%.3f' % opds[-1])
