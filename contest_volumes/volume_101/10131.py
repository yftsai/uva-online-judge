# #dynamic_programming #easy
from sys import stdin

elephants = []
for line in stdin:
    size, iq = map(int, line.split())
    elephants.append((size, iq, len(elephants) + 1))

elephants = sorted(elephants)

sequences = []
longest = None
for j in range(0, len(elephants)):
    prev = (1, None)
    for i in range(0, j):
        if elephants[i][0] < elephants[j][0] \
            and elephants[i][1] > elephants[j][1] \
            and sequences[i][0] + 1 > prev[0]:
            prev = (sequences[i][0] + 1, i)
    sequences.append(prev)
    longest = j if longest == None or prev[0] > sequences[longest][0] else longest

assert(longest != None)
sequence = [longest]
while sequences[ sequence[-1] ][1] != None:
    sequence.append(sequences[ sequence[-1] ][1])
sequence = list(map(lambda i: elephants[i][2], reversed(sequence)))
print(len(sequence))
for elephant in sequence:
    print(elephant)
