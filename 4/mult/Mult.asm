//multiplier
//Alexander Sahlstrom
// set RAM2 to 0
@2
M=0

// set D to RAM0
@0
D=M

// check if RAM0 == 0
@IS_ZERO
D;JEQ

// set D to RAM1
@1
D=M

// check if RAM1 == 0
@IS_ZERO
D;JEQ

// set RAM3 to RAM1
(CHECK)
@3
M=D-1

// set D to RAM0
@0
D=M

// add D to RAM2 (ANSWER)
@2
M=D+M

// set D to RAM3 (COUNTER)
@3
D=M

// if COUNTER > 0, jump to CHECK
@CHECK
D;JGT

// jump to end of program
@END
0;JMP

(IS_ZERO)
@2
M=D
@END
0;JMP

(END)
@END
0;JMP