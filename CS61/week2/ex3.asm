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
	;-----------------
	;INSTRUCTIONS
	;-----------------
	LDI	R3,	DEC_65		;loads address into R3
	LDI	R4,	HEX_41
	
	LD	R5, DEC_65		; get malue from DEC_65 and stores in R5
	LD	R6, HEX_41
	
	LDR R3, R5, #0		;store value in R5 in R3
	LDR R4, R6, #0
	
	ADD  R3, R3, #1
	ADD  R4, R4, #1
	
	STR	R3,	R5, #0		;store value of R5 into address of R3
	STR	R4,	R6,	#0
	
	HALT
	;-------------------
	;LOCAL DATA
	;-------------------
	DEC_65	.FILL	x4000
	HEX_41	.FILL	x4001
	;-------------------
	;REMOTE DATA
	;-------------------
.orig x4000
	NEW_DEC_65 .FILL #65
	NEW_HEX_41 .FILL x41
	
.end

;LDR R1, R5, #0

