from sys import stdin

t = int(stdin.readline())
stdin.readline()
for case in range(0, t):
    distance = int(stdin.readline())
    distances = [0]
    prices = [None]
    while True:
        line = stdin.readline().strip()
        if len(line)==0:
            break
        else:
            d, p = map(int, line.split())
            if d <= distance:
                distances.append(d)
                prices.append(p)
    distances.append(distance)
    prices.append(None)

    costs = {100: 0}
    for i in range(0, len(distances)-1):
        d = distances[i+1] - distances[i]
        if d > 200:
            arrival_costs = {}
        elif prices[i] == None:
            arrival_costs = {(g-d): c for g, c in costs.items() if g >= d}
        else:
            arrival_costs = {}

            for gas, cost in costs.items():
                min_departure_gas = max(d, gas)
                max_departure_gas = min_departure_gas if prices[i+1] and prices[i] > prices[i+1] else 200
                for departure_gas in range(min_departure_gas, max_departure_gas+1):
                    c = cost + prices[i]*(departure_gas-gas)
                    arrival_costs[departure_gas-d] = min(arrival_costs.get(departure_gas-d, c), c)
        costs = arrival_costs

    costs = [c for g, c in costs.items() if g>=100]
    if case>0:
        print()
    if not costs:
        print("Impossible")
    else:
        print(min(costs))
