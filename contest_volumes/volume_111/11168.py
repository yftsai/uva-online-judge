# #geometry #convex_hull
# * The airport/line must pass through a house/point. Otherwise, moving it to a
#   point makes the average distance shorter.
# * The line must be along an edge. While attaching to a point, the line could
#   be rotated, and distances to the line relates to some sin function
#   independently. All the gradients within [0, pi) are decreasing, so the
#   minimum of sum of distances must be on the edges of the convex hull.
# * The distances of all points to the line can be computed in O(1).
from math import sqrt

substract = lambda v1, v2: (v1[0] - v2[0], v1[1] - v2[1])
get_length = lambda v: sqrt(v[0]**2 + v[1]**2)
cross = lambda v1, v2: v1[0] * v2[1] - v1[1] * v2[0]

for t in range(int(input())):
    points = [ tuple(map(int, input().split())) for _ in range(int(input()))]

    start = min(points, key = lambda p: (p[1], p[0]))
    ps = list(filter(lambda p: p != start, points))
    ps = sorted(ps, key = lambda p: (p[0] - start[0]) / get_length(substract(p, start)), reverse = True)
    convex = [start]
    for p in ps:
        while len(convex) > 1 and cross(substract(convex[-1], convex[-2]), substract(p, convex[-1])) < 0:
            convex.pop()

        v = substract(convex[-1], convex[-2]) if len(convex) >= 2 else None
        w = substract(p, convex[-1])
        if len(convex) == 1:
            convex.append(p)
        elif cross(v, w) == 0 and get_length(substract(p, convex[-2])) > get_length(v):
            convex[-1] = p
        elif cross(v, w) > 0 and cross(w, substract(convex[0], p)) > 0:
            convex.append(p)

    avg_distance = None
    s = (sum(p[0] for p in points), sum(p[1] for p in points))
    for i in range(len(convex)):
        v = substract(convex[(i+1)%len(convex)], convex[i])
        w = (s[0] - convex[i][0]*len(points), s[1] - convex[i][1]*len(points))
        d = 0 if get_length(v) == 0 else cross(v, w) /len(points) /get_length(v)
        avg_distance = d if avg_distance == None else min(avg_distance, d)
    print("Case #%d: %.3f" % (t+1, avg_distance))
