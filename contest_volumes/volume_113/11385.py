# #easy
fib_indexes = {1: 0, 2: 1}
f, g = 1, 2
for i in range(2, 101):
    f, g = g, f + g
    fib_indexes[g] = i

for _ in range(int(input())):
    input()
    numbers = map(int, input().split())
    chars = filter(lambda c: 'A' <= c and c <= 'Z', input())
    text = []
    for f in numbers:
        i = fib_indexes[f]
        if i >= len(text):
            text += " " * (i + 1 - len(text))
        text[i] = next(chars)
    print("".join(text))
