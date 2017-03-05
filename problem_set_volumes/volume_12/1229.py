# #easy
# The problem description may look confusing. The extendable sub-dictionary
# could be extended word by word to the whole dictionary.
from sys import stdin

while True:
    n = int(stdin.readline())
    if n == 0:
        break

    d = {}
    in_degrees = {}
    for _ in range(0, n):
        words = stdin.readline().split()
        d[ words[0] ] = set(words[1:])
        for w in d[ words[0] ]:
            in_degrees[w] = in_degrees.get(w, 0) + 1

    removable_words = [w for w in d.keys() if in_degrees.get(w, 0) == 0]
    while removable_words:
        word = removable_words.pop()
        if word in d:
            for w in d[word]:
                in_degrees[w] -= 1
                if in_degrees[w] == 0:
                    removable_words.append(w)
            del d[word]

    print(len(d))
    print(" ".join(sorted(d.keys())))
