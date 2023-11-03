// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.


(INPUTLOOP)


//store the screen address for manipulation
@SCREEN
D=A
@screenaddress
M=D

//end address
@8191
D=A
@screenaddress
D=D+M
@screenend
M=D

//jump to blackout and skip whiteout routine
@KBD
D=M
@BLACKOUT
D;JEQ

(SCREENFILL)

@screenaddress
A=M //dereference address to value
M=0

//increment address to the next 16 bit address
@1
D=A
@screenaddress
M=D+M
D=M

//end if we've reached 8000 into the screen
@screenend
D=M-D

@SCREENFILL
D;JGE

@INPUTLOOP
0;JMP

(BLACKOUT)

@screenaddress
A=M //dereference address to value
M=-1

//increment address to the next 16 bit address
@1
D=A
@screenaddress
M=D+M
D=M

//end if we've reached 8000 into the screen
@screenend
D=M-D

@BLACKOUT
D;JGE


@INPUTLOOP
0;JMP