# #trivial
ndeck = []
for suit in ('Clubs', 'Diamonds', 'Hearts', 'Spades'):
    for v in range(2, 11):
        ndeck.append("%d of %s" % (v, suit))
    for v in ('Jack', 'Queen', 'King', 'Ace'):
        ndeck.append("%s of %s" % (v, suit))

ncases = int(input())
input()

for nc in range(ncases):
    n = int(input())
    shuffles = []
    while len(shuffles) < n or len(shuffles[-1]) < 52:
        order = list(map(int, input().split()))
        while len(order) > 0:
            if len(shuffles) == 0 or len(shuffles[-1]) == 52:
                e = min(52, len(order))
                shuffles.append(order[:e])
            else:
                e = min(52 - len(shuffles[-1]), len(order))
                shuffles[-1].extend(order[:e])
            order = order[e:]

    deck = list(ndeck)
    try:
        while True:
            s = int(input())
            deck = [ deck[i - 1] for i in shuffles[s - 1] ]
    except:
        pass

    if nc > 0:
        print()
    for card in deck:
        print(card)
