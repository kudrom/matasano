#!/usr/bin/env python
from binascii import unhexlify

with open("hex") as f:
    line = f.readline()
nn = int(len(line) / 2)
l = [line[2*i:2*i+2] for i in range(nn)]
hxs = [unhexlify(i) for i in l]

with open("hex.bin", "wb") as f:
    for hx in hxs:
        f.write(hx)
