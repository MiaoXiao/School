;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: ex1
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
	LD R1, DATA_PTR			;load address x4000 into R1
	
	LDR	R2,	R1, #0			;loads value in address x4000 into R2
	LDR	R3,	R1, #1			;loads value in address x4001 into R3
	
	ADD  R2, R2, #1			;R2 <- R2 + 1
	ADD  R3, R3, #1			;R3 <- R3 + 1
	
	STR	R2,	R1, #0			;store value of R2 into x4000
	STR	R3,	R1,	#1			;store value of R3 into x4001
	
	HALT
	;-------------------
	;LOCAL DATA
	;-------------------
	;DEC_65	.FILL	x4000
	;HEX_41	.FILL	x4001
	DATA_PTR	.FILL	x4000
	
	;-------------------
	;REMOTE DATA
	;-------------------
.orig x4000
	NEW_DEC_65 .FILL #65
	NEW_HEX_41 .FILL x41
	
	
.end
