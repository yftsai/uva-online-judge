# #dynamic_programming
set_number = 1
while True:
    n, q = map(int, input().split())
    if n == 0:
        break
    numbers = []
    for _ in range(n):
        numbers.append(int(input()))

    print('SET %d:' % set_number)
    set_number += 1
    query_number = 1
    for _ in range(q):
        d, m = map(int, input().split())
        counts = [ [0 for _ in range(d)] for _ in range(m)]
        for n in numbers:
            for i in range(m - 2, -1, -1):
                for r in range(len(counts[i])):
                    counts[i + 1][(r + n) % d] += counts[i][r]
            counts[0][n % d] += 1
        print('QUERY %d: %d' % (query_number, counts[m - 1][0]))
        query_number += 1
