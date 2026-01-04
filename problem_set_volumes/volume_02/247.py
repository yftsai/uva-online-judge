# #strongly_connected_component
def print_circle(names, calls, i, vindexes, vindex, stack, on_stack):
    vindexes[i] = vindex
    lowlink = vindex
    vindex += 1
    stack.append(i)
    on_stack[i] = True

    for j in calls[i]:
        if vindexes[j] is None:
            vindex, low = print_circle(names, calls, j, vindexes, vindex, stack, on_stack)
            lowlink = min(low, lowlink)
        elif on_stack[j]:
            lowlink = min(vindexes[j], lowlink)

    if vindexes[i] == lowlink:
        while stack[-1] != i:
            print(names[stack[-1]], end = ", ")
            on_stack[stack[-1]] = False
            stack.pop()
        print(names[i])
        on_stack[i] = False
        stack.pop()

    return vindex, lowlink

data_no = 1
while True:
    n, m = map(int, input().split())
    if n == 0:
        break

    names = []
    indexes = {}
    calls = {}
    for _ in range(m):
        n1, n2 = input().split()
        for name in n1, n2:
            if name not in indexes:
                i = len(names)
                indexes[name] = i
                names.append(name)
                calls[i] = []
        i1 = indexes[n1]
        if i1 not in calls:
            calls[i1] = []
        calls[i1].append(indexes[n2])

    if data_no > 1:
        print()
    print("Calling circles for data set %d:" % data_no)
    data_no += 1

    vindex = 0
    vindexes = [None] * n
    stack = []
    on_stack = [False] * n
    for i in range(len(names)):
        if vindexes[i] is None:
            vindex, _ = print_circle(names, calls, i, vindexes, vindex, stack, on_stack)
