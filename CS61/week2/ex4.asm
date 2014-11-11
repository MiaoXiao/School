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
	;-----------------
	;INSTRUCTIONS
	;-----------------
	LD	R0,	NUM1
	LD	R1,	NUM2
	
	DO_WHILE_LOOP
		OUT
		ADD R0, R0, #1
		ADD R1, R1, #-1
		BRp DO_WHILE_LOOP
	END_DO_WHILE_LOOP
	
	HALT
	;-------------------
	;LOCAL DATA
	;-------------------
	NUM1	.FILL	x61
	NUM2	.FILL	x1A

	;-------------------
	;REMOTE DATA
	;-------------------
	
.end

;LDR R1, R5, #0

