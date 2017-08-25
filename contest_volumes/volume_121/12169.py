# #arithmetic
from math import sqrt

m = 10001

# (ins[1] - ins[0]) *  a**2 == (ins[2] - ins[1]) + 10001 * k
def generate_a(ins):
    if ins[1] >= ins[0]:
        p = ins[1] - ins[0]
        right = (ins[2] - ins[1]) if  ins[2] >= ins[1] else (ins[2] - ins[1] + m)
    else:
        p = ins[0] - ins[1]
        right = (ins[1] - ins[2]) if ins[1] >= ins[2] else (ins[1] - ins[2] + m)

    a, left = 0, 0
    while a < m:
        if left < right:
            a = int(sqrt(right/p)) + 1
            left = p * a**2
        elif left > right:
            right += (left - right) //m * m
            right += m if left > right else 0
        else:
            yield a
            a += 1
            left = p * a**2

# ins[0] * a**2 + a * b + b = ins[1] + 10001 * k
def generate_b(ins, a):
    right = ins[1]
    right += (ins[0] * a**2 // m + 1) * m
    right -= ins[0] * a**2
    right %= m
    b = 0
    while b < m:
        if (a + 1) * b < right:
            b = right // (a + 1) + (0 if right % (a + 1) == 0 else 1)
        elif (a + 1) * b > right:
            right += ((a + 1) * b - right) //m *m
            right += m if (a + 1) * b > right else 0
        else:
            yield b
            b += 1

def validate(ins, a, b):
    return all((((ins[i] *a + b) %m *a + b) %m == ins[i+1]) for i in range(len(ins) - 1))

n = int(input())
ins = []
for _ in range(n):
    ins.append(int(input()))

if len(ins) == 1:
    a, b = 1, 0
elif len(ins) == 2:
    a, b = 1, next(generate_b(ins, 1))
else:
    a, b = next(((a, b) for a in generate_a(ins) for b in generate_b(ins, a) if validate(ins, a, b)))

for i in ins:
    print((i * a + b) % m)
