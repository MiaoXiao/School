;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: ex3
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
	LD R3, COUNTER			;R3 <- Counter
	LD R1, VALUE			;R1 <- values to insert in array
	LD R5, ASCII			;R5 <- ascii offset
	
DO_WHILE_LOOP1			;STORE VALUES IN ARRAY
	STR R1, R4, #0			;store R1 in Array
	ADD R1, R1, R1			;multiply value by 2
	
	ADD R4, R4, #1			;increment array
	ADD R3, R3, #-1			;decrement counter
	BRp DO_WHILE_LOOP1
END_DO_WHILE_LOOP1
	
	LD R4, ARRAY_PTR		;reset array pos
	LD R3, COUNTER			;reset counter
	LDR R2, R4, #6			;R2 <- 7th value in array
	

	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	VALUE		.FILL	#2
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

