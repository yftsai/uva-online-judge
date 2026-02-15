from sys import stdin

def put(line):
    """Prints the part of `line` that does not need to be bufferred
       and returns the part that needs to be buffered."""
    if all(c == ' ' for c in line):
        print()
        return None
    else:
        while line != None and len(line) > 72:
            i = line.rfind(' ', 0, 73)
            if i == -1:
                j = line.find(' ', 73)
                if j == -1: j = len(line)
                print(line[:j])
                line = line[j:].lstrip()
            else:
                print(line[:i].rstrip())
                line = line[i:].lstrip()
            if line == '': line = None
        return line

buffer = None

for line in stdin:
    line = line.rstrip('\n')
    if buffer == None:
        buffer = put(line)
    elif len(line) == 0:
        print(buffer.rstrip())
        print()
        buffer = None
    elif line[0] == ' ':
        print(buffer.rstrip())
        buffer = put(line)
    else:
        i = line.find(' ')
        i = i if i > 0 else len(line)
        j = len(buffer) + 1 + i
        if j <= 72:
            buffer += ' ' + line
            buffer = put(buffer)
        else:
            print(buffer.rstrip())
            buffer = put(line)

if buffer != None:
    print(buffer.rstrip())
