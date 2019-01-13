# #easy
from math import gcd

case_number = 1
while True:
    numbers = list(map(int, input().split()[1:]))
    if len(numbers) == 0:
        break
    else:
        num = sum(numbers)  # numerator
        den = len(numbers)  # denominators

        result = [""]
        if num < 0:
            result[0] += "- "
            num = -num

        g = gcd(num, den)
        num //= g
        den //= g

        if num == 0 or num >= den:
            a = str(num // den)
            num = num % den
            result[0] += a
        if num > 0:
            s = len(result[0])
            result = [" " * s, result[0], " " * s]
            num, den = str(num), str(den)
            s = max(len(num), len(den))
            result[0] += ("%" + ("%d" % s) + "s") % num
            result[1] += ("-" * s)
            result[2] += ("%" + ("%d" % s) + "s") % den

        print("Case %d:" % case_number)
        case_number += 1
        for s in result:
            print(s)
