# #easy #dynamic_programming
max_value = 44
counts = [ [0 for _ in range(max_value + 1 - start)] for start in range(max_value + 1) ]

for start in range(max_value + 1):
    counts[start][0] = 1

for d in range(1, max_value + 1):
    for a1 in range(max_value + 1 - d):
        for a2 in range(a1 + 1, a1 + d + 1):
            if a2 % (a2 - a1) == 0 and all(b % (a2 - a1) > 0 for b in range(a1+1, a2+1) if b != a2):
                counts[a1][d] += counts[a2][a1 + d - a2]

while True:
    a1, a2 = map(int, input().split())
    if a1 == 0 and a2 == 0:
        break
    else:
        print(a1, a2, counts[a1][a2 - a1])
