# #easy
def output(bs, width, index = 0, indent = 0):
    b_str = "%d" % bs[index]
    if index < len(bs) - 1:
        next_indent = indent + len(b_str) + 3
        r = (width - next_indent) //2
        print("." *(width - 1 - r), '1', "." *r, sep = '')
        print('.' *indent, b_str, '.+.', "-" *(width - next_indent), sep = '')
        output(bs, width, index + 1, next_indent)
    else:
        print("." * (width - len(b_str)) + b_str)

case_count = 0
while True:
    p, q = map(int, input().split())
    if p == 0:
        break
    else:
        case_count += 1
        print("Case %d:" % case_count)
        print(p, "/", q)
        bs = []
        while q > 0:
            if p % q == 0:
                bs.append(p//q - 1)
                bs.append(1)
            else:
                bs.append(p//q)
            p, q = q, p % q
        width = sum([len("%d" % b) for b in bs]) + 3 * (len(bs) - 1)
        output(bs, width)
