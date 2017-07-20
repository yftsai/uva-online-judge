# #trivial
for _ in range(int(input())):
    a, b = map(int, input().split())
    print('<' if a < b else ('=' if a == b else '>'))
