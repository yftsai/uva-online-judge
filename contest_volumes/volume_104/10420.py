# #trivial
counts = {}
for _ in range(int(input())):
    country = input().split()[0]
    counts[country] = counts.get(country, 0) + 1

for country in sorted(counts.keys()):
    print(country, counts[country])
