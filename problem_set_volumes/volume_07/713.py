# #easy
for _ in range(int(input())):
    m, n = input().split()
    sum = "%d" % (int(m[::-1]) + int(n[::-1]))
    print(int(sum[::-1]))
