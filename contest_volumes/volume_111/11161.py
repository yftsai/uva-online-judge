# #easy
f, g = 1, 1
s, t = 0, 1
numbers = []
for _ in range(1500):
    numbers.append(s + (f - 1) // 2)
    s, t = t, (t + g)
    f, g = g, (f + g)

set_number = 0
while True:
    n = int(input())
    if n == 0:
        break
    else:
        set_number += 1
        print("Set %d:" % set_number)
        print(numbers[n - 1])
