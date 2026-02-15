# #trivial
try:
    while True:
        _, l, c = map(int, input().split())

        col = 0
        line = 0
        for word in input().split():
            if col == 0:
                col += len(word)
            elif col + 1 + len(word) <= c:
                col += 1 + len(word)
            else:
                line += 1
                col = len(word)

        print(line // l + 1)

except EOFError:
    pass
