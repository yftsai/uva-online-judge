# #dynamic_programming
for _ in range(int(input())):
    line = input()
    m = len(line)

    begins = [ [] for _ in range(m) ]
    for i in range(m):
        for j in range(1, min(i + 1, m - i)):
            if line[i - j] != line[i + j]:
                break
            else:
                begins[i + j].append(i - j)
        if i > 0 and line[i - 1] == line[i]:
            begins[i].append(i - 1)
            for j in range(1, min(i, m - i)):
                if line[i - 1 - j] != line[i + j]:
                    break
                else:
                    begins[i + j].append(i - 1 - j)

    npartitions = [0]
    for i in range(m):
        npartitions.append(npartitions[-1] + 1)
        for b in begins[i]:
            npartitions[-1] = min(npartitions[b] + 1, npartitions[-1])
    print(npartitions[-1])
