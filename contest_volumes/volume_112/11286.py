# #trivial
while True:
    n = int(input())
    if n == 0:
        break
    else:
        popularities = dict()
        students = dict()
        for i in range(n):
            courses = tuple(sorted(list(map(int, input().split()))))
            popularities[courses] = popularities.get(courses, 0) + 1
            if not courses in students:
                students[courses] = set([i])
            else:
                students[courses].add(i)

        highest_popularity = max(p for _, p in popularities.items())
        print(sum(len(s) for c, s in students.items() if popularities[c] == highest_popularity))
