# #dynamic_programming
# Is there a simpler approach?

# "count" recursively generates numbers from the most significant digits, and
# returns the count of numbers with the specified patten.
# The number under generation is described by some prefix followed by a
# sequence. Only the sequence possible to be extended to the pattern is
# preserved. The prefix are digits safe to be ignored, but whether it is empty
# determines whether leading zeros are allowed in the sequence under generation.
# Since the prefix is not explicitly preserved, the value limitation bounds the
# maximum after it.
def count(counts, limit, pattern, is_empty_prefix = True, sequence = ""):
    if len(pattern) > len(limit) or (len(pattern) == len(limit) and pattern > limit):
        return 0
    elif len(sequence) > len(limit) or sequence > limit:
        return 0
    elif not all(sequence[i] == pattern[i] for i in range(len(sequence))):
        if len(limit) == 1:
            return 0
        elif sequence[0] == limit[0]:
            return count(counts, limit[1:], pattern, False, sequence[1:])
        else:
            return count(counts, "9" * (len(limit) - 1), pattern, False, sequence[1:])
    elif len(sequence) == len(pattern):
        if len(sequence) == len(limit):
            return 1
        elif limit[:len(sequence)] == sequence:
            return int(limit[len(sequence):]) + 1
        else:
            return 10 ** (len(limit) - len(sequence))
    elif (limit, is_empty_prefix, len(sequence)) in counts:
        return counts[(limit, is_empty_prefix, len(sequence))]
    else:
        r = range(1 if is_empty_prefix and len(sequence) == 0 and len(limit) > 1 else 0, 10)
        c = sum(count(counts, limit, pattern, is_empty_prefix, sequence + str(i)) for i in r)
        if is_empty_prefix and len(sequence) == 0 and len(limit) > 1:
            c += count(counts, "9" * (len(limit) - 1), pattern, is_empty_prefix, sequence)
        counts[(limit, is_empty_prefix, len(sequence))] = c
        return c

from sys import stdin

for line in stdin:
    a, b, n = line.split()
    if a != '-1':
        counts = dict()
        c = count(counts, b, n)
        c -= count(counts, a, n)
        c += 1 if a.find(n) >= 0 else 0
        print(c)
