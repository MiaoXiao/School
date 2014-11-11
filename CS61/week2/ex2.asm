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
	LDI	R3,	DEC_65
	LDI	R4,	HEX_41
	
	ADD  R3, R3, #1
	ADD  R4, R4, #1
	
	STI	R3,	DEC_65
	STI	R4,	HEX_41
	
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

