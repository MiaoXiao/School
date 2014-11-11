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
	LEA	R3, ARRAY				;R3 <- Contents of array
	LD	R1, COUNT				;R1 <- Counter

	
	DO_WHILE_LOOP1			;GET INPUT AND STORE IN ARRAY
		GETC					;input
		OUT						;output
		
		STR	R0, R3, #0			;Store value of output into R3 (array)
		
		ADD R3, R3, #1			;increment array position
		ADD R1, R1, -#1			;count down
		BRp DO_WHILE_LOOP1
	END_DO_WHILE_LOOP1	
	
	
	
	LEA R3, ARRAY				;reset array
	LD R1, COUNT				;reset counter
		
	DO_WHILE_LOOP2			;OUTPUT EACH DATA, SEPERATED BY A NEW LINE
		LD R0, NEWLINE			;output newline
		OUT
		
		LDR R0, R3, #0			;get value of R3 and put in R0
		OUT						;output
		
		ADD R3, R3, #1		
		ADD R1, R1, -#1
		BRp DO_WHILE_LOOP2
	END_DO_WHILE_LOOP2
	
	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	ARRAY	.BLKW	#10			;reserve 10 spaces for array at x3000
	COUNT	.FILL	#10			;counter
	NEWLINE	.FILL	#10			;asci newline
	
	;------------------------------------------------------------------
	;REMOTE DATA
	;------------------------------------------------------------------

	
	
.end

