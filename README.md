# MVM
Maarten Virtual Machine  
Basically a computer that runs machine code from MASM  

# Building
I have built this using Code::Blocks. If you were to try to compile this, be sure to use C++17 STD.

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

## List of opcodes
For far jump use any operand mode that takes 2 like rr, r8, rm to utilize 16-bit address space.

Opcode, name, arguments  
0000 - move (MOV) rr r8 mr rm  
0001 - halt (HLT)  
0010 - in byte (IN) rr r8  
0011 - out byte (OUT) rr r8  
0100 - jump (JMP) rr r8 rm r- m- 8-  

# Serial I/O ports
[0000] Serial COM port

