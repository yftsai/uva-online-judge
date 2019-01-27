# #easy
t = int(input())
for case_number in range(1, t + 1):
    input()
    count = 0
    cover_count = 0
    for c in input():
        if c == '#' or cover_count > 0:
            cover_count -= 1
        else:
            count += 1
            cover_count = 2

    print("Case %d: %d" % (case_number, count))
