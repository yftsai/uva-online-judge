# #easy
ndataset = int(input())
input()

dnames = [ 'N', 'NE', 'E', 'SE', 'S', 'SW', 'W', 'NW' ]
dirs = { 'N': (-1, 0), 'NE': (-1, 1),
         'E': (0, 1),
         'SE': (1, 1), 'S': (1, 0), 'SW': (1, -1),
         'W': (0, -1),
         'NW': (-1, -1) }

def extract(square, row, col, d, n):
    while 0 <= row < len(square) and 0 <= col < len(square[row]):
        if square[row][col] != ' ':
            yield square[row][col]
        row, col = row + d[0], col + d[1]

for dsno in range(ndataset):
    square = []
    n = int(input())
    for _ in range(n):
        square.append(input())

    try:
        if dsno > 0:
            print()
        while True:
            word = input()
            if word == '':
                break

            print()
            print(word)
            has_found = False
            for row in range(n):
                for col in range(n):
                    if square[row][col] == word[0]:
                        for dn in dnames:
                            d = dirs[dn]
                            line = extract(square, row, col, dirs[dn], len(word))
                            if all(word[i] == next(line, None) for i in range(len(word))):
                                print(f'({row + 1},{col + 1}) - {dn}')
                                has_found = True
            if not has_found:
                print('not found')
    except EOFError:
        pass
