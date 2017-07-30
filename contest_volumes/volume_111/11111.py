# #stack #easy
from sys import stdin

for line in stdin:
    state = []
    for size in map(int, line.split()):
        if size < 0 and len(state) == 0:
            state.append((-size, -size -1))
        elif size < 0 and -size <= state[-1][1]:
            state[-1] = (state[-1][0], state[-1][1] + size)
            state.append((-size, -size -1))
        elif size > 0 and len(state) > 0 and state[-1][0] == size:
            state.pop()
        else:
            state.append(None)
            break

    print(":-) Matrioshka!" if len(state) == 0 else ":-( Try again.")
