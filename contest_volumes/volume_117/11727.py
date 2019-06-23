# #trivial
t = int(input())
for test_number in range(1, t + 1):
    salaries = list(map(int, input().split()))
    salaries.sort()
    print("Case %d: %d" % (test_number, salaries[1]))
