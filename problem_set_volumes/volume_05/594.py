# #easy
import sys

bs = [0] * 4
for line in sys.stdin:
    oval = int(line)

    bs[0] = 2 ** 32 + oval if oval < 0 else oval
    for i in range(3):
        bs[i + 1] = bs[i] // 256
        bs[i] %= 256

    nval = 0
    for b in bs:
        nval = nval * 256 + b
    if bs[0] >= 128:
        nval = -(2 ** 32 - nval)

    print(f"{oval} converts to {nval}")
