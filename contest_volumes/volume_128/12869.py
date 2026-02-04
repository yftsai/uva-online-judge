# #trivial
while True:
    low, high = map(int, input().split())
    if low == 0:
        break

    print(high // 5 - low // 5 + 1)
