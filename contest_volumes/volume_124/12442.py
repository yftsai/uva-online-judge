# #cycle_detection
case_count = int(input())
for case_number in range(1, case_count + 1):
    n = int(input())
    recipients = [None] * n
    for _ in range(n):
        u, v = map(int, input().split())
        recipients[u - 1] = v - 1

    counts = [0] * n
    is_visited, stack = [False] * n, []
    for i in range(n):
        if counts[i] == 0:
            is_visited[i] = True
            stack.append(i)
            while len(stack) > 0:
                u, v = stack[-1], recipients[ stack[-1] ]
                is_visited[u] = True
                if counts[v] > 0:
                    counts[u] = counts[v] + 1
                    stack.pop()
                elif is_visited[v]:
                    cycle_size = len(stack) - next(i for i in range(len(stack)) if stack[i] == v)
                    for _ in range(cycle_size):
                        counts[ stack[-1] ] = cycle_size
                        stack.pop()
                else:
                    stack.append(v)
    max_count = max(counts)
    print('Case %d: %d' % (case_number, next((m + 1) for m in range(n) if counts[m] == max_count)))
