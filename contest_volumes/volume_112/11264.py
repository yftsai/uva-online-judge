# #greedy
for _ in range(int(input())):
    input()
    last_count, last_amount = 0, 0
    count, amount = 0, 0
    for c in map(int, input().split()):
        if amount < c:
            last_count, last_amount = count, amount
        count, amount = last_count + 1, last_amount + c
    print(count)
