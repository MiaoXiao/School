;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: ex4
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
	LD R1, ONE				;R1 <- values to insert in array
	LD R5, ASCII			;R5 <- ascii offset
	
	LD R6, ONE
	
DO_WHILE_LOOP1			;STORE VALUES IN ARRAY
	STR R1, R4, #0			;store R1 in Array
	ADD R1, R1, R1			;multiply value by 2
	
	ADD R4, R4, #1			;increment array
	ADD R3, R3, #-1			;decrement counter
	BRp DO_WHILE_LOOP1
END_DO_WHILE_LOOP1
	
	LD R4, ARRAY_PTR		;reset array pos
	LD R3, COUNTER			;reset counter
	LD R1, COUNTER2			;R1 <- new counter
	LDR R2, R4, #6			;R2 <- 7th value in array
	
DO_WHILE_LOOP3			;OUTPUT EACH BINARY STATEMENT

	;store used registers
	ST R3, STORE_R3
	ST R2, STORE_R2
	
	LD R2, ZERO
	
	LDR R3, R4, #0
	
	
	DO_WHILE_LOOP4		;OUTPUT EACH BIT
	
		ADD R3, R3, #0
		BRzp IS_POSITIVE
			ADD R0, R6, R5		;offset	
			OUT
			BRnzp DONE
			
		IS_POSITIVE		
		ADD R0, R2, R5			;offset
		OUT						;output
		
		
	DONE
		ADD R3, R3, R3			;multiply by 2
		ADD R1, R1, #-1			;counter
		BRp DO_WHILE_LOOP4
		
		
	END_DO_WHILE_LOOP4
	
	
	;load old registers
	LD R3, STORE_R3
	LD R2, STORE_R2
	
	LD R0, NEWLINE			;output newline
	OUT
	
	LD R1, COUNTER2			;reset counter
	
	ADD R4, R4, #1
	ADD R3, R3, #-1
	BRp DO_WHILE_LOOP3
END_DO_WHILE_LOOP3

	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	COUNTER		.FILL	#10
	COUNTER2	.FILL	#16
	ARRAY_PTR	.FILL	x4000
	ASCII		.FILL 	#48
	NEWLINE		.FILL	#10
	
	STORE_R3	.BLKW	#1
	STORE_R2	.BLKW	#1

	ZERO		.FILL	#0
	ONE			.FILL	#1
	
	
	;------------------------------------------------------------------
	;REMOTE DATA
	;------------------------------------------------------------------
.orig x4000
	ARRAY	.BLKW	#10			;reserve 10 spaces for array at x4000

.end
