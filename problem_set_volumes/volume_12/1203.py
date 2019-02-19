# #easy
from queue import PriorityQueue

q = PriorityQueue()
while True:
    query = input().split()
    if query[0] == "#":
        break
    else:
        qnum, p = int(query[1]), int(query[2])
        q.put((p, qnum, p))

for _ in range(int(input())):
    t, qnum, p = q.get()
    q.put((t + p, qnum, p))
    print(qnum)
