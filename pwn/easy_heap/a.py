x = "\x08\x19\x00\x06\x15\x04\x16\x04\x1c\x2a\x00\x12\x0a\x2a\x50\x53\x5d\x41\x54\x1c"
asuri = "nuaa"
flag = ''
for i in range(len(x)):
    flag += chr( ord(x[i]) ^ ord(asuri[i%4]) )

print(flag)

