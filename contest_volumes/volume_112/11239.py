# #trivial
while True:
    project = input().strip()
    if project == '0':
        break

    projects = {}
    counts = {}
    counts[project] = 0

    while project != '0' and project != '1':
        sid = input().strip()
        if sid == '1':
            break
        elif 'A' <= sid[0] <= 'Z':
            project = sid
            counts[project] = 0
            continue
        else:
            if not(sid in projects):
                projects[sid] = project
                counts[project] = counts.get(project, 0) + 1
            elif projects[sid] != project:
                projects[sid], p = None, projects[sid]
                if p != None: counts[p] -= 1

    for nc, p in sorted((-c, p) for p, c in counts.items()):
        print(p, -nc)
