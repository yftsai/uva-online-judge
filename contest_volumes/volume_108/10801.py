# #shortest_path
try:
    while True:
        n, k = map(int, input().split())
        elevator_times = list(map(int, input().split()))
        elevator_floors = [set(map(int, input().split())) for _ in range(n)]

        times = [(0 if f == 0 else None) for f in range(100)]
        floors, min_floors = set([0]), set()
        while len(floors) > 0:
            floor = min(floors, key = lambda f: times[f])
            floors.remove(floor)
            min_floors.add(floor)
            for e in (e for e in range(n) if floor in elevator_floors[e]):
                for f in elevator_floors[e]:
                    t = times[floor] + (0 if times[floor] == 0 else 60) + elevator_times[e] * abs(f - floor)
                    if times[f] == None or t < times[f]:
                        times[f] = t
                        floors.add(f)
        print('IMPOSSIBLE' if times[k] == None else times[k])
except EOFError:
    pass
