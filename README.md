# RVM
A simple register virtual machine in C++.

### Table of contents
- [RVM](#rvm)
  * [General](#general)
  * [How to build](#how-to-build)
    + [Windows (Visual Studio 2019)](#windows--visual-studio-2019-)
    + [Debian](#debian)
  * [How to install(Unix only)](#how-to-install)
  * [VM architecture](#vm-architecture)
    + [Registers](#registers)
    + [Instructions](#instructions)
- [RVMAssembler](#rvmassembler)

## General
RVM is a cross platform register based, turing complete VM with stack memory. RVM also includes an assembler with similar syntax to x86 asm with intel syntax.

## How to build
Build instructions have been tested on Windows and Debian based linux distros

### Windows (Visual Studio 2019)

You need to have Visual Studio 2019 and cmake installed on your system.\
Visual Studio 2019 is compatible with cmake projects so you can build the project by opening the project in visual studio, right click the root CMakeLists.txt -> "Generate Cache for NanoVM". This will generate the cmake cache for you and now you can build the project by selecting 
from the menu bar: Build -> Build all.\
If you rather wish to generate visual studio specific build files you can do that by running the following command in the project root with cmd/powershell:

```
cmake . -B ./build
```

This will generate new Visual Studio build files under build/

### Debian

You need to have build tools and cmake available. You can install those by running the following commands in terminal 
```
sudo apt install build-essentials
sudo apt install cmake
```
Now to build the project run the following commands
```
git clone https://github.com/etsubu/NanoVM.git
cd NanoVM
cmake .
make
```
This will build all the binaries in their own folders along the source files.

## How to install
NOTE: Unix only
Go to the releases tab, download the installation package. Extract the files from the installation package, then follow the instructions specified in instructions.txt.

## VM architecture

The VM memory are defined as pages which by default are 4096 bytes each. When initialized the VM bytecode will be placed at the bottom of the allocated memory followed by the stack memory base on the next page. While the VM is similiar to x86 the stack grows up unlike in x86. This can be utilized to dynamically increase the stack memory if required with minimal effort.

### Registers
The VM is register based so the instuctions utilize different registers. Registers are encoded with 3 bits so there are 8 registers in total (the names will change in future):

| Register        | Number        | Description                                  |
| -------------   |:-------------:| --------------------------------------------:|
| Reg0            | 0             | General purpose. Used to store return values |
| Reg1            | 1             | General purpose.                             |
| Reg2            | 2             | General purpose.                             |
| Reg3            | 3             | General purpose.                             |
| Reg4            | 4             | General purpose.                             |
| Reg5            | 5             | General purpose.                             |
| Reg6            | 6             | General purpose.                             |
| Esp             | 7             | Stack pointer. Points to the top of the stack|

### Instructions
Instructions have always an opcode and 0-2 operands. Below is the instruction encoding defined from LSB to MSB

| 5 bits           | 3 bits                | 1 bit             | 2 bits                      | 1 bits        | 1 bit         | 3 bits        |
| -------------    |:---------------------:|:-----------------:|:---------------------------:|:-------------:|:-------------:|:-------------:|
| Opcode           | Destination register  | Source type       | Source size                 | Is_Dst_pointer| Is_Src_pointer|Source register|
| What instruction | Update this register  | Reg=0, Immediate=1| Byte, short, dword, qword   | True,false    | True, false   | Source register if src type is reg|

So most of the instructions are encoded in 2 bytes + immediate value if used. Instructions that use zero operands effectively being only 1 byte are:
```assembly
Halt ; Stops the execution and exits the VM execution
ret ; Pops value from the top of the stack and performs absolute jump to that address. Updates stack pointer
```
Instructions that use 1 operand do not use either source register or immediate value. They do not use destination register even though it is always defined. Opcodes that use 1 operand:
```assembly
	Jz; Jump if zero flag is set. Example: jz reg0
	Jnz; Jump if zero flag is not set. Example: jnz reg0
	Jg;  Jump if greater flag is set. Example: jg reg0
	Js;  Jump if smaller flag is set. Example: js reg0
	Jmp; Jump ("goto") instruction. Example: jmp reg0
	Not; Flip the bits in value. Example: not reg0
	Inc; Increases the value by one: Example inc reg0
	Dec; Decreases the value by one: Example dec reg0
	Call; Pushes the next instructions absolute memory address to the stack and performs relative jump to the given address. Updates stack pointer Example: call reg0
	Push; Pushes value to the top of the stack. Example: push reg0
	Pop; Pops value from the top of the stack and moves the value to given address. Example: pop reg0
	Printi; prints given integer. Example: printi reg0
	Prints; prints given null terminated string. Example: prints @reg0 | Note that @reg0 uses reg0 as pointer to the string not as an absolute value
	Printc; prints given ASCII char to the console. Example printc reg0
```
Instructions with 2 operands:
```assembly
	Mov; mov reg0, reg0 <=> reg0 = reg0
	Add; add reg0, reg0 <=> reg0 += reg0
	Sub; mov reg0, reg0 <=> reg0 -= reg0
	And; mov reg0, reg0 <=> reg0 &= reg0
	Or;  or reg0, reg0 <=> reg0 |= reg0
	Xor; xor reg0, reg0 <=> reg0 ^= reg0
	Sar; sar reg0, reg0 <=> reg0 >>= reg0
	Sal; sal reg0, reg0 <=> reg0 <<= reg0
	Ror; ror reg0, reg0 <=> performs circular shift to the right on reg0, by reg0 times
	Rol; rol reg0, reg0 <=> performs circular shift to the left on reg0, by reg0 times
	Mul; mul reg0, reg0 <=> reg0 *= reg0
	Div; div reg0, reg0 <=> reg0 /= reg0
	Mod; mod reg0, reg0 <=> reg0 %= reg0
	Cmp; cmp reg0, reg1 | Compares the 2 values and sets flags depending on the comparison.
```
ToDo:
* Remove print instructions and move them under the syscall instruction to operate with stream pointers. This allows the printing to support console IO and for example file IO
* Implement syscall instruction

# RVMAssembler
RVMAssembler is currently a minimalistic assembler for RVM. The assembler was made to aid in making simple programs and tests.
Currently the assembler supports comments with prefix ';' and uses regex to filter multiple whitespaces to help in processing the input. The assembler also suppors labels which are defined by ':' prefix. This will be mapped to a memory address that points to the next instruction after label. Example:
```assembly
; The assembler supports comments
; The assembler strips multiple whitespaces
;          xor        reg0,     reg1 
; The above line would be translated to the one below. So the assembler is not sensitive with whitespaces
xor reg0, reg0 ; zero out reg0
:label
printi reg0 ; Label points here
printc '\n' ; The assembler can map characters defined with '' and special characters line \n \r \t to their ascii values
; The above line is the same as printc 10
inc reg0 ; reg0++
cmp reg0, 0x10 ; compare reg0 to 0x10 in hex which is the same as cmp reg0, 10
; The assembler understands base10 and base16 values
jnz label    ; if reg0 != 10 jump to label
; The above code will print numbers
```
ToDo:
* Add macros. These would help to reduce the amount of code that needs to be written.
* Add include tags which would allow to write "standard libraries" which could be included to the project
* Size definitions for registers
* ...

The assembler projects code is not currently clean and the development for that will be most likely be stopped eventually and a new compiler project will be started. Probably with external library for parsing the programming language. I will try and keep the assembler simple.
