;--------------------------------------
; Feng, Rica
; Login: rfeng(rfeng001@ucr.edu)
; Section: 22
; TA: Aditya Tammewar
; assn1
;--------------------------------------

;--------------------------------------------------------
;REG VALUES			R0	R1	R2	R3	R4	R5	R6	R7
;--------------------------------------------------------
;Pre-Loop			0	0	12	6	0	0	0	1168
;Iteration1			0	12	12	5	0	0	0	1168
;Iteration2			0	24	12	4	0	0	0	1168
;Iteration3			0	36	12	3	0	0	0	1168
;Iteration4			0	48	12	2	0	0	0	1168
;Iteration5			0	60	12	1	0	0	0	1168
;End of Program		0	72	12	0	0	0	0	DEC_0
;--------------------------------------------------------

.orig x3000
	;-----------------
	;INSTRUCTIONS
	;-----------------
	LD R1, DEC_0		;R1<--#0
	LD R2, DEC_12		;R2<--#12
	LD R3, DEC_6		;R3<--#6
	
	DO_WHILE_LOOP
		ADD R1, R1, R2		;R1<--R1 + R2
		ADD R3, R3, #-1		;R3<--R3 - #1
		BRp DO_WHILE_LOOP	;if (R3 > 0); goto DO_WHILE LOOP
	END_DO_WHILE_LOOP
	
	HALT					;HALT PROGRAM (like exit in c++)
	;-------------------
	;LOCAL DATA
	;-------------------
	DEC_0	.FILL	#0		;put #0 into memory here
	DEC_12	.FILL	#12		;put #12 into memory here
	DEC_6	.FILL	#6		;put #6 into memory here

.end
