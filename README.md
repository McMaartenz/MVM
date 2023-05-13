# MVM
Maarten Virtual Machine  
Basically a computer that runs machine code from MASM

# Opcodes
Format of an instruction:
oooo sssR rrr1 rrr2 cccc cccc
oooo sssR cccc cccc
oooo sssR

- unused
o opcode
s selection 00:reg reg 01:reg im8 10: mem reg 11: reg mem 100: no arguments 101: just reg 110: just mem 111: just im8
r1,r2 registers
R memory is relative to IP
c constant, or memory

Opcode, name, arguments
0000 - move (MOV) rr r8 mr rm
0001 - halt (HLT)

