# #easy
def verify(weighting, coin, is_heavy):
    for w in weighting:
        if coin in w[0] and w[2] != ("up" if is_heavy else "down"):
            return False
        elif coin in w[1] and w[2] != ("down" if is_heavy else "up"):
            return False
        elif not(coin in w[0]) and not(coin in w[1]) and w[2] != "even":
            return False
    return True

coins = list(map(chr, range(ord('A'), ord('L') + 1)))
is_heavy = (True, False)

for _ in range(int(input())):
    weighting = [input().split() for _ in range(3)]

    c, h = next(((c, h) for c in coins for h in is_heavy if verify(weighting, c, h)))
    print(c, "is the counterfeit coin and it is", "heavy." if h else "light.")
