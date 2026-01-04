# #trivial

def mark_eagle(image, pos, q):
    n = len(image)
    image[pos[0]][pos[1]] = '*'
    q.append(pos)

    while len(q) > 0:
        x, y = q[-1]
        q.pop()

        for i in range(max(0, x - 1), min(x + 2, n)):
            for j in range(max(0, y - 1), min(y + 2, n)):
                if image[i][j] == '1':
                    image[i][j] = '*'
                    q.append((i, j))

try:
    image_no = 1
    q = []
    while True:
        image = []
        n = int(input())
        for i in range(n):
            image.append(list(input()))

        count = 0
        for i in range(n):
            for j in range(n):
                if image[i][j] == '1':
                    mark_eagle(image, (i, j), q)
                    count += 1

        print("Image number %d contains %d war eagles." % (image_no, count))
        image_no += 1

except:
    pass
