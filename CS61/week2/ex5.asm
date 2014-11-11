;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: ex5
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
	;input output
	TRAP x23
	
	LEA R1, MSG_TO_PRINT	;R1<-the location of the label,MSG_TO_PRINT						
	
	;ITERATE THROUGH STRING
	DO_WHILE_LOOP
		LDR R0, R1, #0
		OUT
		ADD R1, R1, #1
		BRnp DO_WHILE_LOOP
	END_DO_WHILE_LOOP
	
	HALT
	;-------------------
	;LOCAL DATA
	;-------------------
	MSG_TO_PRINT	.STRINGZ	"GAMESPAWN\n"

	;-------------------
	;REMOTE DATA
	;-------------------
	
.end
