;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: assn3
; Lab section: 22
; TA: Aditya Tammewar
;
; I hereby certify that the contents of this file
; are ENTIRELY my own original work.
;
;=================================================
.orig x3000
	;------------------------------------------------------------------
	;INSTRUCTIONS
	;------------------------------------------------------------------
	LD R3, NUMB				;R3 <- number to convert to bits
	
	LD R1, ZERO				;R1 <- zero
	LD R2, ONE				;R2 <- one	
	LEA R4, ARRAY			;R4 <- 16 reserved spots for array
	LD R5, COUNTER			;R5 <- Counter, loop 16 times
	LD R6, ASCII			;R6 <- offset
	
DO_WHILE_LOOP2			;INPUT BITS
	ADD R3, R3, #0			
	BRzp IS_POSITIVE
		STR	R2, R4, #0		;if number is positive or 0, add ONE bit
	IS_POSITIVE
	
	ADD R3, R3, #0			
	BRn IS_NEGATIVE	
		STR R1, R4,	#0		;if number is negative, add ZERO bit
	IS_NEGATIVE
	
	
	ADD R3, R3, R3			;multiply number by 2
	ADD R4, R4, #1			;increment array position
	ADD R5, R5, #-1			;decrement counter
	BRp DO_WHILE_LOOP2
END_DO_WHILE_LOOP2



	LEA R4, ARRAY			;reset array
	LD R5, COUNTER			;reset counter


		
DO_WHILE_LOOP3			;OUTPUT EACH BIT
	LDR R0, R4, #0			;get value at array pos and put in R0
	ADD R0, R0, R6			;add offset
	OUT						;output
		
	ADD R4, R4, #1			;increment array position
	ADD R5, R5, -#1			;decrement counter
	BRp DO_WHILE_LOOP3
END_DO_WHILE_LOOP3

	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	ARRAY	.BLKW	#16			;reserve 16 spaces for array at x3000
	
	ZERO	.FILL	#0			;bit
	ONE		.FILL	#1			;bit
	
	ASCII	.FILL	#48			;ascii offset
	COUNTER	.FILL	#16			;counter for loops
	
	NUMB	.FILL	#169		;number to convert to bits
	
	;------------------------------------------------------------------
	;REMOTE DATA
	;------------------------------------------------------------------
.end
