# #dynamic_programming
try:
    is_first_case = True
    transform_insert = 'Insert'
    transform_delete = 'Delete'
    transform_replace = 'Replace'
    while True:
        string1 = input()
        string2 = input()
        transform_table = []

        transform_table.append([])
        transform_table[-1].append((0, None))
        for j in range(len(string2)):
            transform_table[-1].append((transform_table[0][j][0] + 1, transform_insert))
        for i in range(len(string1)):
            transform_table.append([(transform_table[-1][0][0] + 1, 'Delete')])
            for j in range(len(string2)):
                insert = transform_table[i + 1][j][0]
                delete = transform_table[i][j + 1][0]
                replace = transform_table[i][j][0]
                if string1[i] == string2[j]:
                    transform_table[-1].append((replace, None))
                elif insert <= delete and insert <= replace:
                    transform_table[-1].append((insert + 1, transform_insert))
                elif delete <= replace:
                    transform_table[-1].append((delete + 1, transform_delete))
                else:
                    transform_table[-1].append((replace + 1, transform_replace))

        transform_list = []
        i, j = len(string1), len(string2)
        while i > 0 or j > 0:
            t = transform_table[i][j][1]
            if t == None:
                i, j = i - 1, j - 1
            elif t == transform_insert:
                transform_list.append((transform_table[i][j][1], j, string2[j - 1]))
                j -= 1
            elif t is transform_delete:
                transform_list.append((transform_table[i][j][1], j + 1))
                i -= 1
            else:
                transform_list.append((transform_table[i][j][1], j, string2[j - 1]))
                i, j = i - 1, j - 1

        if is_first_case:
            is_first_case = False
        else:
            print()
        transform_list = list(reversed(transform_list))
        print(len(transform_list))
        for i in range(len(transform_list)):
            if transform_list[i][0] is transform_insert:
                print(i + 1, "%s %i,%s" % transform_list[i])
            elif transform_list[i][0] is transform_delete:
                print(i + 1, "%s %i" % transform_list[i])
            else:
                print(i + 1, "%s %i,%s" % transform_list[i])
except:
    pass
