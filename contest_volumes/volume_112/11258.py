# #dynamic_programming
for _ in range(int(input())):
    line = input()
    sums = [0 for _ in range(len(line))]
    for j in range(len(line)):
        for i in range(max(0, j - 9), j + 1):
            n = int(line[i:(j + 1)])
            if n < 2**31:
                if i == 0:
                    sums[j] = n
                else:
                    sums[j] = max(sums[j], sums[i - 1] + n)
    print(max(sums))
