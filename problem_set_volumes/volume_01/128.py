# #easy
from sys import stdin

for line in stdin:
    if line[0] == '#':
        break
    else:
        crc, g = 0, 34943
        for c in line.rstrip('\n'):
            crc = ((crc << 8) + ord(c)) % g
        crc = (crc << 16) % g
        crc = 0 if crc == 0 else (g-crc)
        print("%02X %02X" % (crc >> 8, crc % 256))
