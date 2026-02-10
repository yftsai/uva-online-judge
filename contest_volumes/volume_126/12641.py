# #trivial
def as_key(w):
    return w[0] + "".join(sorted(w[1:-1])) + w[-1]

for _ in range(int(input())):
    words = {}
    for w in input().split():
        k = as_key(w)
        words[k] = words.get(k, w)
    print(" ".join(words.get(as_key(w), w) for w in input().split()))
