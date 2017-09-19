# #easy #long_common_subsequence
from itertools import count

for d in count(1):
    seqs = [input(), None]
    if seqs[0] == '#':
        break
    else:
        seqs[1] = input()
        lengths = [ list(0 for _ in range(len(seqs[0]) + 1)) for _ in range(2) ]
        for c in seqs[1]:
            lengths[0], lengths[1] = lengths[1], lengths[0]
            for i in range(len(seqs[0])):
                if seqs[0][i] == c:
                    lengths[1][i + 1] = lengths[0][i] + 1
                else:
                    lengths[1][i + 1] = max(lengths[0][i + 1], lengths[1][i])
        print("Case #%d: you can visit at most %d cities." % (d, lengths[1][-1]))
