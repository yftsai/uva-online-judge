# #easy
from sys import stdin
import re

words = set()
hypenated = None

for line in stdin:
    line = line.lower()
    ws = re.findall(r'[a-zA-Z\-]+', line)

    if hypenated != None:
        if len(line) > 0 and 'a' <= line[0] <= 'z':
            if len(ws) == 1:
                if line[-2] == '-':
                    hypenated += ws[0][:-1]
                else:
                    words.add(hypenated + ws[0])
                    hypenated = None
                ws = []
            else:
                words.add(hypenated + ws[0])
                hypenated = None
                ws = ws[1:]
        else:
            words.add(hypenated)
            hypenated = None

    words.update(ws[:-1])
    if len(ws) > 0:
        w = ws[-1]
        if w[-1] == '-' and line[-1] == '\n':
            hypenated = w[:-1]
        else:
            words.add(w)

for w in sorted(words):
    print(w)
