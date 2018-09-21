# #easy #union
case_count = int(input())

def find(parents, i):
    j = i
    while parents[i] != i:
        i = parents[i]
    while j != i:
        parents[j], j = i, parents[j]
    return i

def union(parents, sizes, a, b):
    i = find(parents, a - 1)
    j = find(parents, b - 1)

    if i == j:
        return sizes[i]
    else:
        parents[i] = j
        sizes[i], sizes[j] = 0, (sizes[i] + sizes[j])
        return sizes[j]

for _ in range(case_count):
    n, m = map(int, input().split())
    parents = [i for i in range(n)]
    sizes = [1 for _ in range(n)]
    largest = 1
    for _ in range(m):
        a, b = map(int, input().split())
        largest = max(largest, union(parents, sizes, a, b))
    print(largest)
