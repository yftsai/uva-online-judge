# #trivial
for case_number in range(1, int(input()) + 1):
    count_ages = input().split()
    count = int(count_ages[0])
    print('Case %d: %s' % (case_number, count_ages[count // 2 + 1]))
