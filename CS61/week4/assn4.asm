;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: assn4
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
	ERRORGO							;code will jump here if wrong input
	
	LD R0, ZERO						;R0 <- default
	
	ST R0, STORE_R0					;reset local data
	ST R0, STORE_R1
	ST R0, STORE_R6
	
	LD R1, ZERO						;R1 <- default is 0
	LD R2, CPOS						;R2 <- checks for certain characters
	
	LD R3, MCOUNT					;R3 <- Counter for multiplication
	LD R4, ASCII					;R4 <- offset
	LD R5, COUNT					;R5 <- Counter, loop 5 times
	LD R6, ZERO						;R6 <- default
	
	LEA R0, CALL					;R0 <- ask for user input
	PUTS
	
	LD R0, NEWLINE					;newline
	OUT
	
	GETC							;get sign
	OUT
	
	ADD R2, R2, R0					;check if pos number
	BRnp IS_POS
	
		BRnzp DONE2
	IS_POS
	
	LD R2, CNEG						;change check to check for negatives
	
	ADD R2, R2, R0
	BRnp IS_NEG
		LD R6, ONE					;R6 <- One, signifies negative number
		ST R6, STORE_R6				;Store R6 for later use
		BRnzp DONE2
	IS_NEG
	
	LD R2, ERRORCHECK1				;ERROR CHECKING BEGIN
	ST R0, STORE_R0
	ADD R0, R0, R2					;check if ascii is lower than 0
	BRp	IS_ERROR
		BRnzp WRONG
	IS_ERROR
	
	LD R0, STORE_R0
	LD R2, ERRORCHECK2
	
	ADD R0, R0, R2					;check if ascii is higher than 9
	BRn	IS_ERROR2
		BRnzp WRONG
	IS_ERROR2
	
	LD R0, STORE_R0
	LD R2, CNEW						;ERROR CHECKING END
	
	BRnzp DONE2
	
	WRONG							;future errors will jump here
	
	LD R0, NEWLINE					;newline
	OUT
	OUT
	
	LEA R0, ERROR					;error message
	Puts
	
	LD R0, NEWLINE					;newline
	OUT
	OUT
	
	BRnzp ERRORGO					;jump to start
	
	DONE2
	GETC							;get first number and simply input into R1
	OUT
	
	LD R2, ERRORCHECK1				;ERROR CHECKING BEGIN
	ST R0, STORE_R0
	ADD R0, R0, R2					;check if ascii is lower than 0
	BRp	IS_ERROR
		BRnzp WRONG
	IS_ERROR
	
	LD R0, STORE_R0
	LD R2, ERRORCHECK2
	
	ADD R0, R0, R2					;check if ascii is higher than 9
	BRn	IS_ERROR2
		BRnzp WRONG
	IS_ERROR2
	
	LD R0, STORE_R0
	LD R2, CNEW						;ERROR CHECKING END
	
	ADD R0, R0, R4
	ADD R1, R1, R0
	
	LD R2, CNEW
DO_WHILE_LOOP1						;CHANGE R1
	GETC
	OUT
	
	ADD R2, R2, R0					;check if newline
	BRz IS_NEWLINE
	
		LD R2, ERRORCHECK1				;ERROR CHECKING BEGIN
		ST R0, STORE_R0
		ADD R0, R0, R2
		BRp	IS_ERROR
			BRnzp WRONG
		IS_ERROR
		
		LD R0, STORE_R0
		LD R2, ERRORCHECK2
		
		ADD R0, R0, R2
		BRn	IS_ERROR2
			BRnzp WRONG
		IS_ERROR2
			
		LD R0, STORE_R0
		LD R2, CNEW						;ERROR CHECKING END
	
		ADD R0, R0, R4				;offset
		;store register
		ST R1, STORE_R1
		
									;load registers (copy R0 to R6)
		LD R6, STORE_R1				;store R0 in R6
		
		
		Multiply					;MULTIPLY R1 BY 10
			ADD R1, R1, R6			;add R1 with R1
			ADD R3, R3, #-1			;decrement mcounter
			BRp Multiply
		END_Multiply
		LD R3, MCOUNT				;reset multiplication counter

		ADD R1, R1, R0				;add number to R1
		BRnzp DONE
	IS_NEWLINE
	
		ADD R5, R5, #-5				;set counter to negative and quit loop if newline was entered
	
	DONE
	LD R2, CNEW						;reset check
	ADD R5, R5, #-1					;decrement counter
	BRp DO_WHILE_LOOP1
END_DO_WHILE_LOOP1

	LD R6, STORE_R6					;load back true/false statement if number is negative

	ADD R6, R6, #-1					;if R6 changes to 0, number is negative
	BRnp TWOCOMP
		NOT R1, R1
		ADD R1, R1, #1
	TWOCOMP

	LD R0, NEWLINE					;end program with newline
	OUT
	
	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	ZERO		.FILL	#0					;bit
	ONE			.FILL	#1					;bit
	
	COUNT		.FILL	#5					;counter for loops
	MCOUNT		.FILL	#9					;counter for multiplication
	
	ASCII		.FILL	#-48				;ascii offset
	
	CPOS		.FILL	#-43				;checks for pos
	CNEG		.FILL	#-45				;checks for neg
	CNEW		.FILL 	#-10				;checks if newline
	NEWLINE		.FILL	#10					;asci newline
	
	ERRORCHECK1	.FILL	#-47				
	ERRORCHECK2	.FILL 	#-58
	
	STORE_R0	.BLKW	#1
	STORE_R1	.BLKW	#1
	STORE_R6	.BLKW	#1
	
	CALL	.stringz	"Input a positive or negative decimal number (max 5 digits), followed by ENTER"
	ERROR	.stringz	"Error! Please try again."
	;------------------------------------------------------------------
	;REMOTE DATA

.end

