// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

//set R2 to 0
@2
M=0

//if either inputs are 0, end
@0
D=M
@END
D;JEQ

@1
D=M
@END
D;JEQ

(LOOP)
//Load R2 
@2
D=M

//Add R0
@0
D=D+M

//Store in R2
@2
M=D

//Decrement iterator R1
@1
D=M
D=D-1
M=D

//loop if iterator > 0
@LOOP
D;JGT

(END)
@END
0;JMP