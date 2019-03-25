try:
    case_number = 1
    products = []

    while True:
        # consume n
        input()

        products.clear()
        maxp = 0
        for v in map(int, input().split()):
            if v == 0:
                products.clear()
            elif len(products) == 0:
                products.append(1)
            elif len(products) == 1 and products[0] < 0:
                products.append(1)

            for i in range(len(products)):
                products[i] *= v
            maxp = max(maxp, max((p for p in products), default = 0))

        print("Case #%d: The maximum product is %d." % (case_number, maxp))
        print()
        case_number += 1

        # consume the empty line or throw an exception at EOF
        input()
except:
    pass
