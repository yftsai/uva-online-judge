# #easy
for _ in range(int(input())):
    k = int(input()) - 1    # 0-indexed
    configs = []
    for c in range(2):
        configs.append([set() for _ in range(5)])
        for _ in range(6):
            row = input()
            for i in range(len(row)):
                configs[-1][i].add(row[i])

    config = []
    for i in range(5):
        config.append(sorted(configs[0][i] & configs[1][i]))

    pwd_count = 1
    for cs in config:
        pwd_count *= len(cs)

    if k < pwd_count:
        pwd = ''
        for i in range(5):
            pwd_count = 1
            for j in range(i+1, 5):
                pwd_count *= len(config[j])
            pwd += config[i][k//pwd_count]
            k -= k //pwd_count *pwd_count
    else:
        pwd = 'NO'
    print(pwd)
