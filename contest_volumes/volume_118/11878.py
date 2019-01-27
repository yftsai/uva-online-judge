# #easy
correct_count = 0

try:
    while True:
        formula = input()
        i = next(i for i in range(len(formula)) if formula[i] != ' ')
        j = next(j for j in range(i, len(formula)) if formula[j] == '+' or formula[j] == '-')
        a = int(formula[i:j])
        op = formula[j]

        i, j = j + 1, formula.find('=', j + 1)
        b = int(formula[i: j])

        i, j = j + 1, formula.find('?', j + 1)
        if j == -1:
            correct_c = (a + b) if op == '+' else (a - b)
            correct_count += 1 if int(formula[i:]) == correct_c else 0
except:
    print(correct_count)
