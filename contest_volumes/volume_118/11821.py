# #floating_number
from math import log10, ceil, floor

class hpnumber:
    def __init__(self, number):
        self.sign = -1 if number[0] == '-' else 1
        number = number[1:] if number[0] == '-' else number

        i = number.find('.')
        if i == -1:
            self.set_magnitude(int(number), 0)
        else:
            self.set_magnitude(int(number[:i] + number[i + 1:]), len(number) - 1 - i)

    def set_magnitude(self, v, p):
        if v == 0:
            self.digits, self.decpt = v, 0
        elif v < 10 ** 29:
            e = ceil(log10(10 ** 29 / v))
            self.digits = v * 10 ** e
            self.decpt = 30 - p - e
        elif v >= 10 ** 30:
            e = floor(log10(v / 10 ** 29))
            b = 10 ** e
            carry = 0 if v % b < b / 2 else 1
            self.digits = v // b + carry
            self.decpt = 30 - p + e
        else:
            self.digits = v
            self.decpt = 30 - p

    def increase(self, number):
        d = min(self.decpt, number.decpt)
        v = self.sign * self.digits * 10 ** (self.decpt - d)
        v += number.sign * number.digits * 10 ** (number.decpt - d)

        self.sign = 1 if v >= 0 else -1
        v = v if v >= 0 else -v

        self.set_magnitude(v, 30 - d)

    def __str__(self):
        if self.digits == 0:
            number = "0"
        elif self.decpt <= 0:
            number = "0." + ('0' * -self.decpt) + str(self.digits)
        elif self.decpt < 30:
            number = str(self.digits)
            number = number[:self.decpt] + "." + number[self.decpt:]
        else:
            number = str(self.digits) + "0" * (self.decpt - 30)

        i = max(self.decpt, 1)
        if i < len(number):
            i = max(j for j in range(i, len(number)) if number[j] != '0')
            i = i if number[i] == '.' else (i + 1)

        return ("" if self.digits == 0 or self.sign == 1 else "-") + number[:i]

for _ in range(int(input())):
    acc = hpnumber('0')
    while True:
        number = input()
        if number == '0':
            break
        else:
            acc.increase(hpnumber(number))
    print(acc)
