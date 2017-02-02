#combinatorics

def get_number_of_intersections(n):
    # return sum([i*(n-2-i)+1 for i in range(0, n-1)])
    return (n*n*n - 6*n*n + 17*n - 12)//6

def get_number_of_areas(n):
    # return 1 + sum([get_number_of_intersections(i) for i in range(1, n+1)])
    return 1 + (n*n*(n+1)*(n+1)//4 - n*(n+1)*(2*n+1) + 17*n*(n+1)//2)//6 - 2*n

from sys import stdin

s = int(stdin.readline())
for _ in range(0, s):
    n = int(stdin.readline())
    print(get_number_of_areas(n))
