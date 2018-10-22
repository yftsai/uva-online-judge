# #easy
from sys import stdin

message = []
for line in stdin:
    v = 0
    if len(line) > 0 and line[0] != '_':
        for c in reversed(line):
            if c == '|':
                b = 0
            elif c == ' ' or c == 'o':
                b = max(1, b * 2)

            if c == 'o':
                v += b
        message.append(chr(v))
print("".join(message), end = '')
