# #easy
while True:
    cards = list(map(int, input().split()))
    if cards[0] == 0:
        break
    else:
        win_count = 0
        princess = sorted(cards[:3])
        for c in cards[3:]:
            i = next((i for i in range(len(princess)) if princess[i] > c), None)
            if i == None:
                win_count += 1
                i = 0
            princess[i:(i+1)] = []

        if win_count == 0:
            c = -1
        elif win_count == 1:
            c = next((c for c in range(princess[0] + 1, 53) if not c in cards), -1)
        else:
            c = next(c for c in range(1, 53) if not c in cards)
        print(c)
