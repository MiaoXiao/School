;--------------------------------------------------------------
;Feng, Rica
;Login:rfeng (rfeng001@ucr.edu)
;Section:022
;TA Aditya Tammewar
;Lab 01
;--------------------------------------------------------------
.orig x3000

	;Instrctions
	LD R1, DEC_0	;R1 is #0
	LD R2, DEC_12	;R2 is #12
	LD R3, DEC_6	;R3 is #6

	DO_WHILE_LOOP
		ADD R1, R1, R2		;R1 is R1 + R2
		ADD R3, R3, #-1		;R3 is R3 - #1
		BRp DO_WHILE_LOOP	;if (R3 > 0(: goto DO_WHILE_LOOP)
	END_DO_WHILE_LOOP

	HALT	;exit loop
	
	;Local Data
	DEC_0	.FILL	#0		;put #0 in memory here
	DEC_12	.FILL	#12		;put #12 in memory here
	DEC_6	.FILL	#6		;put #6 in memory here

.end
