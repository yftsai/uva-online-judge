# #trivial
from fractions import Fraction

while True:
    month_count, down_payment, loan_amount, record_count = input().split()
    month_count, down_payment, loan_amount = int(month_count), Fraction(down_payment), Fraction(loan_amount)
    if month_count < 0:
        break
    dep_records = []
    for i in range(int(record_count)):
        record = input().split()
        dep_records.append((int(record[0]), Fraction(record[1])))
    monthly_payment = loan_amount / month_count

    m, r = 0, 0
    car_value = (down_payment + loan_amount) * (1 - dep_records[0][1])
    if car_value <= loan_amount:
        for m in range(1, month_count + 1):
            if r + 1 < len(dep_records) and m >= dep_records[r + 1][0]:
                r += 1
            car_value *= (1 - dep_records[r][1])
            loan_amount -= monthly_payment
            if car_value > loan_amount:
                break
    print(m, "month" if m == 1 else "months")
