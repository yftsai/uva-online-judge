# #trivial

duration = {'W': 64, 'H': 32, 'Q': 16, 'E': 8, 'S': 4, 'T': 2, 'X': 1}
while True:
    line = input()
    if line == '*':
        break
    else:
        measure_count = 0
        d = 0
        for c in line:
            if c == '/':
                if d == 64:
                    measure_count += 1
                d = 0
            else:
                d += duration[c]
        print(measure_count)
