# #easy
def solve(ss):
    s = sum(ss[0:3]) // 2
    ws = [s - ss[2], s - ss[1], s - ss[0]]

    z = ss[-2] - ws[2]
    ws.append(ss[-1] - z)
    ws.append(z)

    return ws

for cn in range(1, int(input()) + 1):
    ss = sorted(map(int, input().split()))

    for i in range(2, 5):
        ss[2], ss[i] = ss[i], ss[2]
        ws = solve(ss)
        ss[2], ss[i] = ss[i], ss[2]

        if sorted([ws[i] + ws[j] for i in range(5) for j in range(i + 1, 5)]) == ss:
            break

    print("Case %d: %s" % (cn, " ".join(map(str, ws))))
