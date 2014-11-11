;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: ex2
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
	LD R4, ARRAY_PTR		;R4 <- 10 reserved spots for array
	LD R3, COUNTER			;R2 <- Counter
	LD R1, VALUE_ZERO		;R1 <- values to insert in array
	LD R5, ASCII			;R5 <- ascii offset
	
DO_WHILE_LOOP1			;STORE VALUES IN ARRAY
	STR R1, R4, #0			;store R1 in Array
	ADD R1, R1, #1			;increment value to insert into array
	
	ADD R4, R4, #1			;increment array
	ADD R3, R3, #-1			;decrement counter
	BRp DO_WHILE_LOOP1
END_DO_WHILE_LOOP1
	
	LD R4, ARRAY_PTR		;reset array pos
	LD R3, COUNTER			;reset counter
	LDR R2, R4, #6			;R2 <- 7th value in array
	
DO_WHILE_LOOP3			;OUTPUT EACH ELEMENT OF ARRAY
	LDR R0, R4, #0			;R0 <- Element of array
	ADD R0, R0, R5			;offset
	OUT						;output
	
	LD R0, NEWLINE			;output newline
	OUT
	
	ADD R4, R4, #1
	ADD R3, R3, #-1
	BRp DO_WHILE_LOOP3
END_DO_WHILE_LOOP3

	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	VALUE_ZERO	.FILL	#0
	COUNTER		.FILL	#10
	ARRAY_PTR	.FILL	x4000
	ASCII		.FILL 	#48
	NEWLINE		.FILL	#10
	
	;------------------------------------------------------------------
	;REMOTE DATA
	;------------------------------------------------------------------
.orig x4000
	ARRAY	.BLKW	#10			;reserve 10 spaces for array at x4000

.end
