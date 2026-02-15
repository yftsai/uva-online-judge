# #sorting
is_first_case = True
while True:
    col = input()
    row = int(input())
    if row == 0:
        break

    rows = [ [None] * len(col) for _ in range(len(col)) ]
    for i in range(len(col)):
        rows[i][-1] = col[i]
    rows = sorted(rows)

    for i in range(2, len(col) + 1):
        for r in range(len(col)):
            rows[r][-i] = col[r]
        rows = sorted(rows)

    if is_first_case:
        is_first_case = False
    else:
        print()
    print("".join(rows[row - 1]))
