# #easy
from sys import stdin

def is_substring_of(s1, s2):
    j = 0
    for c in s1:
        while j < len(s2) and s2[j] != c:
            j += 1
        if j == len(s2):
            return False
        else:
            j += 1
    return True

for line in stdin:
    line = line.rstrip('\n')

    i = line.find(' ')
    j = line.find(' ', i + 1) if i != -1 else -1
    ps = []
    if i != -1 and j != -1:
        s1 = line[:i]
        val = line[i + 1: j]
        s2 = line[j + 1:]
        p = all(c.islower() for c in s1) and len(s1) <= 1000
        p = p and all(c.isdigit() for c in val)
        p = p and all(c.islower() for c in s2) and len(s2) <= 2000
        if p:
            val = int(val)
            p = p and val <= 1000
        ps.append(p)
    else:
        ps.append(False)

    ps.append(ps[0] and s2 == s2[::-1])

    if ps[0]:
        ps.append(all(c in s2 for c in set(c for c in s1)))

        freq1 = {}
        for c in s1:
            freq1[c] = freq1.get(c, 0) + 1
        freq2 = {}
        for c in s2:
            freq2[c] = freq2.get(c, 0) + 1
        ps.append(all(freq1.get(c, 0) <= f for c, f in freq2.items()) and all(c in freq2 for c in freq1))
    else:
        ps.extend([False, False])

    ps.append(ps[0] and is_substring_of(s1, s2))
    ps.append(ps[0] and len(s1) + val == len(s2))
    ps.append(ps[0] and val < len(s1))

    is_accepted = "" if all(ps) else " not"
    print("".join('T' if b else 'F' for b in ps), f"The solution is{is_accepted} accepted")
