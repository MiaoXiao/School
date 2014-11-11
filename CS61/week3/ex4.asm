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
	LEA	R3, ARRAY				;R3 <- Contents of array
	LD R2, CHECK				;R2 <- Checks if newline
	
	DO_WHILE_LOOP1			;GET INPUT AND STORE IN ARRAY
		GETC					;input
		OUT						;output
		
		STR	R0, R3, #0			;Store value of output into R3 (array)
		
		ADD R3, R3, #1			;increment array position	
			
		ADD R0, R0, R2 			;check R0 for new line
		BRnp DO_WHILE_LOOP1
	END_DO_WHILE_LOOP1	

	LEA R3, ARRAY				;reset array 
	
	DO_WHILE_LOOP2			;OUTPUT EACH DATA, SEPERATED BY A NEW LINE
		LD R0, NEWLINE			;output newline
		OUT
		
		LDR R0, R3, #0			;get value of R3 and put in R0
		OUT						;output
		
		ADD R3, R3, #1
		
		ADD R0, R0, R2		
		BRnp DO_WHILE_LOOP2
	END_DO_WHILE_LOOP2
	
	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	CHECK	.FILL 	#-10		;checks if newline
	NEWLINE	.FILL	#10			;asci newline
	ARRAY	.FILL	x4000		;first pos of array
	
	;------------------------------------------------------------------
	;REMOTE DATA
	;------------------------------------------------------------------
.orig x4000
	NEW_ARRAY	.FILL	#0		;empty spot
	
.end

