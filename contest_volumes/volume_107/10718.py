# #binary_number
try:
    while True:
        n, l, u = map(int, input().split())

        msb = 1
        while (msb << 1) <= u:
            msb <<= 1

        m, max_m, b = 0, (msb << 1) - 1, msb
        while b > 0:
            if max_m - b < l:
                m |= b
            elif (m | b) > u:
                max_m -= b
            elif b & n == 0:
                m |= b
            else:
                max_m -= b
            b >>= 1

        print(m)
except:
    pass
