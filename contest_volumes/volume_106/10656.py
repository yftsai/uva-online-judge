# #trivial
while True:
    n = int(input())
    if n == 0:
        break
    else:
        subsequence = []
        for _ in range(n):
            v = int(input())
            if v > 0:
                subsequence.append(v)
        subsequence = subsequence if len(subsequence) > 0 else [0]

        print(" ".join(map(str, subsequence)))
