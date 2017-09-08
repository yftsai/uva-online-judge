# #trivial
for n in range(int(input())):
    wife_time = input().split()
    meeting_time = input().split()
    can_attend = meeting_time[1] < wife_time[0] or meeting_time[0] > wife_time[1]
    print("Case %d: %s" % (n + 1, "Hits Meeting" if can_attend else "Mrs Meeting"))
