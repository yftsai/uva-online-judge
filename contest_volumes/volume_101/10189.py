# #trivial
field_count = 0

while True:
    n, m = map(int, input().split())
    if n == 0:
        break
    else:
        field = []
        for _ in range(n):
            field.append([c for c in input()])
        for r in range(len(field)):
            for c in range(len(field[r])):
                if field[r][c] == '.':
                    n = 0
                    for i in range(max(0, r - 1), min(r + 2, len(field))):
                        for j in range(max(0, c - 1), min(c + 2, len(field[i]))):
                            if field[i][j] == '*':
                                n += 1
                    field[r][c] = str(n)

        field_count += 1
        if field_count > 1:
            print()
        print('Field #%d:' % field_count)
        for r in field:
            print("".join(r))
