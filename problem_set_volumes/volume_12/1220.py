from sys import stdin

employee = {}
bigboss = None

# plan(name) returns
# (n guest when [name] is absent,
#  whether the list is unique when [name] is absent,
#  n guest when [name] is preset,
#  whether the list is unique when [name] is present)
def plan(name):
    p = [0, True, 1, True]

    for e in employee.get(name, []):
        pe = plan(e)

        # plan for the absense of [name]
        p[0] += max(pe[0], pe[2])
        p[1] = p[1] and pe[0] != pe[2] and (pe[1] if pe[0]>pe[2] else pe[3])

        # plan for presence of [name]
        p[2] += pe[0]
        p[3] = p[3] and pe[1]

    return tuple(p)

n = 0
nemployee = 0
for line in stdin:
    if n == 0 or n == nemployee:
        n = int(line)
        employee = {}
        nemployee = 0
    else:
        nemployee += 1
        names = line.split()
        if len(names)==1:
            bigboss = names[0]
        elif names[1] in employee:
            employee[ names[1] ].append(names[0])
        else:
            employee[ names[1] ] = [ names[0] ]

    if n > 0 and n == nemployee:
        p = plan(bigboss)
        if p[0] > p[2]:
            print(p[0], "Yes" if p[1] else "No")
        elif p[0] == p[2]:
            print(p[0], "No")
        else:
            print(p[2], "Yes" if p[3] else "No")
