from sys import stdin

while True:
    m, n = map(int, stdin.readline().split())
    if m == 0:
        break
    member_counts = list(map(int, stdin.readline().split()))
    seat_capacities = list(map(int, stdin.readline().split()))

    assignment = [ [0 for _ in range(0, c)] for c in member_counts]
    is_valid = True
    for team in sorted(range(0, len(member_counts)), key = lambda i: member_counts[i], reverse = True):
        if not is_valid:
            break
        elif member_counts[team] > len(seat_capacities):
            is_valid = False
        else:
            # Sorting in every iteration is inefficient, but n = len(seat_capacities) is small enough.
            table_indexes = sorted(range(0, len(seat_capacities)), key = lambda i: seat_capacities[i], reverse = True)
            for i in range(0, member_counts[team]):
                table = table_indexes[i]
                assignment[team][i] = table + 1
                seat_capacities[table] -= 1
                is_valid = is_valid and (seat_capacities[table] >= 0)
   
    print(1 if is_valid else 0)
    if is_valid:
        for a in assignment:
            print(" ".join(map(str, sorted(a))))
