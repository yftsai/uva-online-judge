# Python 3.5 doesn't support `match`
def is_lying(kinds, name):
    k = kinds[name]
    return k == 'evil' or (k == 'human' and kinds['It'] == 'night')

def verify(statements, kinds):
    for speaker, stats in statements.items():
        is_speaker_lying = is_lying(kinds, speaker)
        for s in stats:
            if s == 'day' or s == 'night':
                if is_speaker_lying == (kinds['It'] == s):
                    return False
            else:
                name = s[0]
                if s[-1] == "lying":
                    if   len(s) == 2 and is_speaker_lying == is_lying(kinds, name):
                        return False
                    elif len(s) == 3 and is_speaker_lying != is_lying(kinds, name):
                        return False
                elif len(s) == 2 and is_speaker_lying == (kinds[name] == s[1]):
                    return False
                elif len(s) == 3 and is_speaker_lying != (kinds[name] == s[2]):
                    return False
    return True

cno = 1
while True:
    n = int(input())
    if n == 0:
        break

    names = set()
    statements = {}
    for i in range(n):
        words = input().split()
        words[-1] = words[-1].replace(".", "")

        speaker = words[0].replace(":", "")
        names.add(speaker)

        if words[1] == "It":
            statements.setdefault(speaker, []).append(words[-1])
        else:
            # There are potential optimizations:
            #   "I am lying." always leads to "This is impossible."
            #   "I am not lying." can be ignored.
            name = speaker if words[1] == 'I' else words[1]
            names.add(name)
            if len(words) == 4:
                statements.setdefault(speaker, []).append((name, words[-1]))
            else:
                statements.setdefault(speaker, []).append((name, False, words[-1]))

    names = sorted(names)

    facts = { n: None for n in names }
    facts['It'] = None
    for states in range(3 ** len(names)):
        kinds = {}
        s = states
        for n in names:
            kinds[n] = ('divine', 'evil', 'human')[s % 3]
            s //= 3
        for i in ('day', 'night'):
            kinds['It'] = i
            if verify(statements, kinds):
                for n, k in facts.items():
                    if k == None:
                        facts[n] = kinds[n]
                    elif k != kinds[n]:
                        facts[n] = False

    print("Conversation #%d" % cno)
    if all(k == None for k in facts.values()):
        print("This is impossible.")
    elif all(k == False for k in facts.values()):
        print("No facts are deducible.")
    else:
        for n in names:
            if facts[n] != False:
                print("%s is %s." % (n, facts[n]))
        if facts['It'] != False:
            print("It is %s." % facts['It'])
    print()
    cno += 1
