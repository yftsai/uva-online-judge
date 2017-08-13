# #trivial
case_count = int(input())
for c in range(case_count):
    input()
    indexes = list(map(int, input().split()))
    numbers = input().split()
    permutation = [None] * len(indexes)
    for i in range(len(indexes)):
        permutation[indexes[i] - 1] = numbers[i]
    if c > 0:
        print()
    for n in permutation:
        print(n)
