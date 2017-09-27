# #dynamic_programming
from sys import stdin
from collections import Counter

sequence = []
for line in stdin:
    sequence.append(tuple(map(int, sorted(line.split()))))

    if len(sequence) == 13:
        scores = dict()
        scores[0] = []

        for i in range(6):
            ss = dict()
            for bitset in scores:
                for r in range(13):
                    if bitset & (1 << r) == 0:
                        bs = bitset | (1 << r)
                        s = scores[bitset] + [ sum(d if d == i + 1 else 0 for d in sequence[r]) ]
                        if (not bs in ss) or sum(ss[bs]) < sum(s):
                            ss[bs] = s
            scores = ss

        for bitset in scores:
            scores[bitset].append(35 if sum(scores[bitset]) >=63 else 0)

        predicates = [
            lambda _: True,
            lambda dices: Counter(dices).most_common(1)[0][1] >= 3,
            lambda dices: Counter(dices).most_common(1)[0][1] >= 4,
            lambda dices: dices[0] == dices[4],
            lambda dices: any(all((i in dices) for i in range(start, start + 4)) for start in range(1, 4)),
            lambda dices: any(all((i in dices) for i in range(start, start + 5)) for start in range(1, 3)),
            lambda dices: Counter(dices).most_common()[0][1] == 5 or (Counter(dices).most_common()[0][1] == 3 and Counter(dices).most_common()[1][1] == 2) ]
        get_scores = [
            sum,
            sum,
            sum,
            lambda _: 50,
            lambda _: 25,
            lambda _: 35,
            lambda _: 40 ]
        for i in range(7):
            ss = dict()
            for bitset in scores:
                for r in range(13):
                    if bitset & (1 << r) == 0:
                        bs = bitset | (1 << r)
                        s = scores[bitset] + [ get_scores[i](sequence[r]) if predicates[i](sequence[r]) else 0 ]
                        if (not bs in ss) or sum(ss[bs]) < sum(s):
                            ss[bs] = s
            scores = ss

        k = 2**13 - 1
        s = scores[k]
        s = s[:6] + s[7:] + s[6:7]
        s.append(sum(s))
        print(" ".join(map(str, s)))

        sequence = []
