# #easy
case_number = 1
while True:
    n = int(input())
    if n == 0:
        break
    else:
        print("Case %d: %d" % (case_number, n / 2 ))
        case_number += 1
