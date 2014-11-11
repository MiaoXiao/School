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
	;-----------------
	;INSTRUCTIONS
	;-----------------
	LEA	R3, ARRAY				;R3 <- Contents of array
	LD	R1, COUNT				;R1 <- Counter

	DO_WHILE_LOOP
		GETC					;input
		OUT						;output
		
		STR	R0, R3, #0			;Store value of output into R3 (array)
		ADD R3, R3, #1			;increment array position
		
		ADD R1, R1, -#1			;count down
		BRp DO_WHILE_LOOP
	END_DO_WHILE_LOOP
	
	HALT
	;-------------------
	;LOCAL DATA
	;-------------------
	ARRAY	.BLKW	#10			;reserve 10 spaces for array at x3000
	COUNT	.FILL	#10

	
	;-------------------
	;REMOTE DATA
	;-------------------

	
	
.end
