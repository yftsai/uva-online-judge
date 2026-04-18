# #easy
for _ in range(int(input())):
    phrase = input().upper()
    key = []
    for c in phrase:
        if c != ' ' and c not in key:
            key.append(c)
    for c in range(ord('A'), ord('Z') + 1):
        d = chr(c)
        if d != 'Q' and d not in key:
            key.append(d)

    text = [c for c in reversed(input().upper()) if c != ' ']
    encrypted  = []
    while len(text) > 0:
        dg = text.pop()
        if len(text) == 0 or dg == text[-1]:
            dg = (dg, 'X')
        else:
            dg = (dg, text.pop())

        i = key.index(dg[0])
        ir, ic = i // 5, i % 5
        j = key.index(dg[1])
        jr, jc = (j // 5, j % 5)
        if ir == jr:
            encrypted.append(key[ir * 5 + (ic + 1) % 5])
            encrypted.append(key[jr * 5 + (jc + 1) % 5])
        elif ic == jc:
            encrypted.append(key[(ir + 1) % 5 * 5 + ic])
            encrypted.append(key[(jr + 1) % 5 * 5 + jc])
        else:
            encrypted.append(key[ir * 5 + jc])
            encrypted.append(key[jr * 5 + ic])

    print("".join(encrypted))
