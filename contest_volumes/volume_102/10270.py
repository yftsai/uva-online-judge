# Without more insight, this problem doesn't seem educational.
#
# There are no obvious optimization properties, and the search space is huge
# for a larger prime number. Though it is obvious to precompute the results,
# getting the difficult ones is still non-trivial.
#
# Using a simple strategy of always diving into smaller rectangles can quickly
# get a good bound. For n = 47, this approach requires 18 squares and the
# minimal is 16. Unfortunately, exploring states of 17 levels is still
# impossible.
#
# Inspecting whether a partial result could be fitted in a square seems
# unlikely. There are ~n**2 possible positions for each small square.
#
# Estimating the minimal number of squares along the edges may be a useful
# property. If the largest piece is not aligned by an edge, the minimal squares
# along the edge can be estimated. They can be used for pruning, but the
# problem of ~n**2 positions remains the same.
# This observation tells that the larger squares are usually by the edges.
# Unfortunately, there are still 10+ small squares not by any edge.
#
# The best bet seems observing patterns from the results of smaller primes.

from collections import Counter

use_unproven_heuristics = True

def overlapped(placements, x, y, sz):
    pred = lambda p: x<p[0]+p[2] and x+sz>p[0] and y<p[1]+p[2] and y+sz>p[1]
    return next((p for p in placements if pred(p)), None)

def place(n, squares, placements = None, x = 0, y = 0):
    if placements == None:
        return place(n, Counter(squares), [], 0, 0)
    elif all(c == 0 for c in squares.values()):
        return placements
    # an unproven heuristics: initially put the largest piece in the corner
    # and second largest squares next to it.
    elif n%2 == 1 and len(placements) == 0 and use_unproven_heuristics:
        m = max(squares.keys())
        assert((n-m) in squares.keys())
        assert(squares[m] == 1)
        # put the largest square at the top left corner
        del squares[m]
        placements.append((0, 0, m))
        # put the second largest next to the largest one
        for i in range(0, min(squares[n-m], m//(n-m)*2)):
            squares[n-m] -= 1
            if i%2 == 0:
                placements.append((i//2*(n-m), m, n-m))
            else:
                placements.append((m, i//2*(n-m), n-m))
        return place(n, squares, placements)
    else:
        # move x, y to the first empty space
        while x <= n-1:
            while y <= n-1:
                o = overlapped(placements, x, y, 1)
                if o != None:
                    y = o[1] + o[2]
                else:
                    break
            if y <= n-1:
                break
            else:
                x, y = x+1, 0
        # put a square on the first empty space
        for w in squares.keys():
            if squares[w]>0 and x<=n-w and y<=n-w and overlapped(placements, x, y, w) == None:
                placements.append((x, y, w))
                squares[w] -= 1
                r = place(n, squares, placements, x, y+w)
                if r != None:
                    return r
                squares[w] += 1
                placements.pop()
        return None

def search_least_squares(n, spaces, squares, bound):
    if sum(squares.values()) >= sum(bound.values()):
        return bound
    elif spaces == 0:
        return Counter(squares) if place(n, squares) else bound
    else:
        max_size = n-1 if len(squares) == 0 else min(min(squares.keys())-1, n-min(squares.keys()))
        for w in range(max_size, 0, -1):
            for c in range(spaces//w//w, spaces-1 if w == 1 else 0, -1):
                squares[w] = c
                bound = search_least_squares(n, spaces - w**2*c, squares, bound)
                del squares[w]
        return bound

count_squares = lambda c: sum(c.values())

def estimate(n, m, table = {}):
    if n == 0 or m == 0:
        return Counter([])
    elif n == m:
        return Counter({n: 1})
    elif n < m:
        return estimate(m, n)
    elif (n, m) in table:
        return table[(n, m)]
    else:
        table[(n, m)] = min((estimate(i, i) + estimate(n-i, i) + estimate(n, m-i) for i in range(1, m+1)), key = count_squares)
        return table[(n, m)]

least_squares = {
    17: Counter({9: 1, 8: 2, 5: 1, 4: 2, 3: 1, 2: 3, 1: 2}),
    19: Counter({13: 1, 6: 4, 4: 1, 3: 2, 2: 3, 1: 2}),
    23: Counter({13: 1, 10: 2, 7: 1, 6: 2, 4: 1, 3: 1, 2: 3, 1: 2}),
    29: Counter({17: 1, 12: 2, 9: 1, 8: 2, 4: 2, 3: 1, 2: 3, 1: 2}),
    31: Counter({21: 1, 10: 4, 7: 1, 4: 3, 3: 1, 2: 3, 1: 2}),
    37: Counter({21: 1, 16: 2, 12: 1, 9: 2, 7: 1, 5: 1, 4: 1, 3: 1, 2: 2, 1: 3}),
    41: Counter({23: 1, 18: 2, 12: 1, 11: 2, 7: 1, 5: 1, 4: 1, 3: 2, 2: 2, 1: 2}),
    43: Counter({29: 1, 14: 4, 8: 1, 7: 2, 5: 1, 3: 3, 2: 2, 1: 2}),
    47: Counter({28: 1, 19: 2, 16: 1, 12: 2, 7: 2, 5: 1, 4: 1, 3: 1, 2: 2, 1: 3}),
    49: Counter({28: 1, 21: 2, 14: 3, 7: 3})
}

def compute_least_squares(n):
    if n in least_squares:
        None
    elif n%2 == 0:
        least_squares[n] = Counter({n//2: 4})
    elif n%3 == 0:
        least_squares[n] = Counter({n//3*2: 1, n//3: 5})
    elif n%5 == 0:
        least_squares[n] = Counter({n//5*3: 1, n//5*2: 3, n//5: 4})
    else:
        # bound by an simple estimation
        least_squares[n] = min((estimate(i, i) + estimate(n-i, i) + estimate(n, n-i) for i in range(1, n)), key = count_squares)
        # bound by factors
        for f in range(2, n):
            if n%f == 0:
                compute_least_squares(f)
                scaled_squares = { k*(n//f): least_squares[f][k] for k in least_squares[f].keys()}
                least_squares[n] = min(least_squares[n], scaled_squares, key = count_squares)

        # an unproven heuristics: the sum of the largest two sizes equals to n
        if n%2 == 1 and use_unproven_heuristics:
            for i in range(n-1, n//2, -1):
                j = n - i
                for c in range((n**2 - i**2)//j//j, 1, -1):
                    init = Counter({i: 1, j: c})
                    least_squares[n] = search_least_squares(n, n**2 - i**2 - j**2*c, Counter({i: 1, j: c}), least_squares[n])
        else:
            least_squares[n] = search_least_squares(n, n*n, Counter(), least_squares[n])

for n in range(2, 51):
    compute_least_squares(n)

t = int(input())
for _ in range(0, t):
    n = int(input())
    placements = place(n, least_squares[n])
    print(sum(least_squares[n].values()))
    for p in placements:
        print(p[0]+1, p[1]+1, p[2])
