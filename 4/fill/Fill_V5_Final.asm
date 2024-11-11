//FILL V5
//Alexander Sahlstrom
(START)
@SCREEN
D=A //set D to SCREEN
@1
M=D //set RAM0 to D 

//if key is NOT pressed, jump to WHITE
//if key is pressed, jump to BLACK
(KBD_CHECK)
@KBD
D=M //set D to KBD

@WHITE
D;JEQ //if D = 0, jump to WHITE (no key pressed)

@BLACK
D;JGT //if D > 0, jump to BLACK (key is pressed)

//WHITE
(WHITE)
@2
M=0 //set RAM1 to 0
@FILL
0;JMP //jump to FILL

//BLACK
(BLACK)
@2
M=-1 //set RAM1 to -1
@FILL
0;JMP //jump to FILL

(FILL)
@2
D=M //setting D to stored value (-1 or 1)

//get address and fill pixel w/ white or black
@1
A=M //set A to RAM0 (SCREEN)
M=D //set RAM0 to D (1 or -1)

//increment to next pixel, check if end of screen is reached
@1
D=M+1 //set D to next line of pixels
@KBD
D=A-D //set D to KBD - D (check if next line is end of screen)


@1
M=M+1 // set RAM0 to next address of next line of pixels
A=M // set A to RAM0

//if not end of screen, jump to CHANGE
@FILL
D;JGT

//end of screen, jump to start
@START
0;JMP
