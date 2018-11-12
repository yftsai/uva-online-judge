# #easy
for _ in range(int(input())):
    line = input()
    stack = []
    for c in line:
        if c == '(' or c == '[':
            stack.append(c)
        elif c == ')' and len(stack) > 0 and stack[-1] == '(':
            stack.pop()
        elif c == ']' and len(stack) > 0 and stack[-1] == '[':
            stack.pop()
        else:
            stack.append(c)
            break
    print('Yes' if len(stack) == 0 else 'No')
