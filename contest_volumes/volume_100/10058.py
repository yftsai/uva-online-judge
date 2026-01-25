# #parsing
from sys import stdin

def parse_statement(tokens, i):
    i = parse_action(tokens, i)
    while i < len(tokens) and tokens[i] == ',':
        i = parse_action(tokens, i + 1)
    return i

verbs = ['hate', 'love', 'know', 'like', 'hates', 'loves', 'knows', 'likes']

def parse_action(tokens, i):
    i = parse_active_list(tokens, i)
    if tokens[i] in verbs:
        return parse_active_list(tokens, i + 1)
    else:
        raise RuntimeError()

def parse_active_list(tokens, i):
    i = parse_actor(tokens, i)
    while i < len(tokens) and tokens[i] == 'and':
        i = parse_actor(tokens, i + 1)
    return i

articles = ['a', 'the']
nouns = ['tom', 'jerry', 'goofy', 'mickey', 'jimmy', 'dog', 'cat', 'mouse']

def parse_actor(tokens, i):
    if tokens[i] in articles:
        i += 1
    if tokens[i] in nouns:
        return i + 1
    else:
        raise RuntimeError()

for line in stdin:
    tokens = line.split()
    try:
        i = parse_statement(tokens, 0)
    except:
        i = -1

    print("YES I WILL" if i == len(tokens) else "NO I WON'T")
