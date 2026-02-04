# #easy #prime_number
from itertools import takewhile
import heapq

def gen_sps(e):
    for b in takewhile(lambda b: b ** e < 2 ** 64, range(1, 2 ** 16)):
        yield b ** e

primes = [2]
exps = []
for n in range(3, 64):
    if all(map(lambda p: n % p != 0, primes)):
        primes.append(n)
    else:
        exps.append(n)

gs = [ gen_sps(e) for e in exps ]
hq = [ (next(gs[i]), i) for i in range(len(gs)) ]
heapq.heapify(hq)

last = 0
while len(hq) > 0:
    sp, i = heapq.heappop(hq)
    if last < sp:
        last = sp
        print(sp)

    sp = next(gs[i], None)
    if sp != None:
        heapq.heappush(hq, (sp, i))
