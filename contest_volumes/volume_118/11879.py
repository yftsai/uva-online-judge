# #trivial
while True:
    n = int(input())
    if n == 0:
        break
    else:
        print(0 if n % 17 > 0 else 1)
