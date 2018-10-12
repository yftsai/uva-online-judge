from sys import stdin

numbers = []
sequence = []
terminator = -999999

def get_max_product(seq):
    max_prod = seq[0]
    for i in range(len(seq)):
        prod = 1
        for j in range(i, len(seq)):
            prod *= seq[j]
            max_prod = max(max_prod, prod)
    return max_prod

for line in stdin:
    numbers.extend(int(n) for n in line.split())
    if len(numbers) > 0 and numbers[-1] == terminator:
        numbers.pop()

        max_prod = numbers[0]
        sequence.clear()
        for n in numbers:
            if n == 0:
                if len(sequence) > 0:
                    max_prod = max(max_prod, get_max_product(sequence), 0)
                    sequence.clear()
            elif n > 0:
                if len(sequence) == 0 or sequence[-1] < 0:
                    sequence.append(n)
                else:
                    sequence[-1] *= n
            else:
                while sum(1 for x in sequence if x < 0) >= 3:
                    sequence[-2] *= sequence[-1]
                    sequence.pop()
                sequence.append(n)
        numbers.clear()

        if len(sequence) > 0:
            max_prod = max(max_prod, get_max_product(sequence))

        print(max_prod)
