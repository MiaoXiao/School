;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: assn5.asm
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
							LD R1, ZERO				;R1 <- Second Number
							LD R2, ZERO				;R2 <- First Number
							LD R4, ZERO				;R4 <- Sign for first number
							LD R3, ZERO				;R3 <- Sign for second number

							LEA R0, CALL
							PUTS

							LD R0, NEWLINE			;newline
							OUT
							
							LD R6, GET_INPUT		;R6 <- Address; Gets a number and possible sign
							JSRR R6					;Get first number
							ADD R4, R3, #0			;move sign from R3 to R4
							
							ST R1, EMPTY			;Copy R1 to R2
							LD R2, EMPTY
							
							LD R6, GET_INPUT		;R6 <- Address; Gets a number
							JSRR R6					;Get second number
							
							LD R6, MULTIPLY			;R6 <- Address; multiplies R1 and R2
							JSRR R6
							
							;DISPLAY THE EQUATION IF THERE IS NO OVERFLOW
							LD R0, DISPLAY_EQUATION
							JSRR R0
	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	CALL		.stringz	"Enter in two numbers (up to five digits each), seperated by a newline."
	
	ASCII		.FILL		#-48
	NEWLINE		.FILL		#10
	ZERO		.FILL		#0
	
	SIGN1		.BLKW		#1
	SIGN2		.BLKW		#1

	EMPTY		.FILL		#6
	
	GET_INPUT			.FILL		x3200
	GET_SIGN			.FILL		x3400
	DISPLAY_EQUATION	.FILL		x3800
	MULTIPLY			.FILL		x4200
	
	;------------------------------------------------------------------
	;REMOTE DATA
	;------------------------------------------------------------------

;----------------------------------------------------------------------------------------------------
; Subroutine Name: GET_INPUT
; Parameter (Register you are “passing” as a parameter): None
; Postcondition: Takes input, up to five digits, and inserts the number into R1
				;R3 holds the sign for that number
; Return Value: R1, R3

; How to call a function: LD R5, [SUBROUTINE NAME]
; Then JSRR R5
; In R5 is the address of your subroutine, with the subroutine name as your label
.orig x3200
;----------------------------------------------------------------------------------------------------

;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values

ST R0, BACKUP_R0_3200
ST R2, BACKUP_R2_3200
ST R4, BACKUP_R4_3200
ST R5, BACKUP_R5_3200
ST R6, BACKUP_R6_3200
ST R7, BACKUP_R7_3200

; (2) Perform whatever algorithm(s) this subroutine is suppose to perform


LD R3, MCOUNTER_3200
LD R4, OFFSET_3200
LD R5, COUNTER_3200
LD R6, ZERO_3200

							GETC							;get first char (sign or number)
							OUT
							
							
							LD R2, CPOS_3200				;CHECKS IF pos sign is present
							
							ADD R2, R2, R0					;check if pos number
BRnp IS_POS1
							LD R3, ZERO_3200
							ST R3, EMPTY_3200				;R3 <- Zero, signifies pos number
							BRnzp DONE5
IS_POS1
							
							LD R2, CNEG_3200					;change check to check for negatives
							
							ADD R2, R2, R0					;check if neg number
BRnp IS_NEG2
							LD R3, ONE_3200
							ST R3, EMPTY_3200				;R3 <- One, signifies negative number
							BRnzp DONE5	
IS_NEG2
							LD R4, STARTRANGE_3200			;load parameters for subroutine
							LD R5, ENDRANGE_3200
							LD R2, BEGIN_ERROR				;address to jump to if error occurs
							
							LD R6, INPUT_VALIDATION			;Check if a valid number. if a valid number if no sign was input
							JSRR R6
							
							LD R3, MCOUNTER_3200
							LD R4, OFFSET_3200				;reload correct variables
							LD R5, COUNTER_3200
							LD R6, ZERO_3200				;reset R6
							
							BRnzp DONE3
DONE5
							
							GETC							;Calling the FIRST digit if a sign was input
							OUT
							
							LD R2, CNEWLINE_3200			;load newline
							ADD R2, R2, R0					;check if newline
							BRz IS_NEWLINE
							
							LD R4, STARTRANGE_3200			;load parameters for subroutine
							LD R5, ENDRANGE_3200
							LD R2, BEGIN_ERROR				;address to jump to if error occurs
							
							LD R6, INPUT_VALIDATION			;R6 <- Address: check if character is valid
							JSRR R6
							
							LD R3, MCOUNTER_3200
							LD R4, OFFSET_3200				;reload correct variables
							LD R5, COUNTER_3200
							LD R6, ZERO_3200				;reset R6
DONE3							
							LD R2, CNEWLINE_3200			;reset check
							
							ADD R0, R0, R4					;offset
							
							ST R0, EMPTY_3200				;copy R0 to R1
							LD R1, EMPTY_3200


GET_INPUT1				
							ST R5, COUNTER_TEMP					;hold counter
							
							GETC
							OUT
							
							ADD R2, R2, R0					;check if newline
							BRz IS_NEWLINE
															;The following will run if newline was NOT entered
							LD R4, STARTRANGE_3200			;load parameters for subroutine
							LD R5, ENDRANGE_3200
							LD R2, MID_ERROR				;address to jump to if error occurs
							
							LD R6, INPUT_VALIDATION			;R6 <- Address: check if character is valid
							JSRR R6
							
							LD R3, MCOUNTER_3200
							LD R4, OFFSET_3200				;reload correct variables
							LD R5, COUNTER_TEMP		
							LD R6, ZERO_3200				;reset R6
							
							ADD R0, R0, R4					;offset
							
							ST R1, EMPTY_3200				;copy R1 to R6
							LD R6, EMPTY_3200
							
	Multiply												;MULTIPLY R1 BY 10
							ADD R1, R1, R6					
							ADD R3, R3, #-1					;decrement mcounter
							BRp Multiply
	END_Multiply
							LD R3, MCOUNTER_3200			;reset multiplication counter

							ADD R1, R1, R0					;add number to R1
							BRnzp DONE
								
							IS_NEWLINE
							
							ADD R5, R5, #-5				;set counter to negative and quit loop if newline was entered
							
							DONE
							LD R2, CNEWLINE_3200			;reset check
							ADD R5, R5, #-1					;decrement counter
							BRp GET_INPUT1
END_GET_INPUT1
							LD R3, SIGN_3200				;pass in return value (sign)
; (3) Restore the registers that you backed up

LD R0, BACKUP_R0_3200
LD R2, BACKUP_R2_3200
LD R4, BACKUP_R4_3200
LD R5, BACKUP_R5_3200
LD R6, BACKUP_R6_3200
LD R7, BACKUP_R7_3200

; (4) RETurn to where you came from
Ret

;------------------------
; Subroutine Data
;------------------------
STARTRANGE_3200		.FILL	#-47
ENDRANGE_3200		.FILL	#-58

SIGN_3200			.BLKW	#1

OFFSET_3200			.FILL	#-48
CNEWLINE_3200		.FILL	#-10
COUNTER_3200 		.FILL	#4
MCOUNTER_3200		.FILL	#9
ONE_3200			.FILL	#1
ZERO_3200			.FILL	#0

CPOS_3200		.FILL	#-43				;checks for pos
CNEG_3200		.FILL	#-45				;checks for neg

EMPTY_3200		.BLKW	#1
COUNTER_TEMP	.BLKW	#1

ERROR_ADDRESS1_3200		.FILL	x3208
ERROR_ADDRESS2_3200		.FILL	x321D
INPUT_VALIDATION		.FILL	x3600

BEGIN_ERROR				.FILL	x3200
MID_ERROR				.FILL	x3200

BACKUP_R0_3200	.BLKW	#1
BACKUP_R2_3200	.BLKW	#1
BACKUP_R4_3200	.BLKW	#1
BACKUP_R5_3200	.BLKW	#1
BACKUP_R6_3200	.BLKW	#1
BACKUP_R7_3200	.BLKW	#1

;----------------------------------------------------------------------------------------------------
; Subroutine Name: GET_SIGN
; Parameter (Register you are “passing” as a parameter): None
; Postcondition: Checks for a sign and puts in R3 a 0 or 1 (0 = positive, 1 = negative)
; Return Value: R3
; How to call a function: LD R5, [SUBROUTINE NAME]
; Then JSRR R5
; In R5 is the address of your subroutine, with the subroutine name as your label
.orig x3400
;----------------------------------------------------------------------------------------------------

;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R0, BACKUP_R0_3400
ST R1, BACKUP_R1_3400
ST R2, BACKUP_R2_3400
ST R4, BACKUP_R4_3400
ST R5, BACKUP_R5_3400
ST R6, BACKUP_R6_3400
ST R7, BACKUP_R7_3400
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
							
							GETC
							OUT
							
							LD R4, EXITOUT					;exitout is an address that will restart program
							
							LD R2, CPOS_3400
							
							ADD R2, R2, R0					;check if pos number
BRnp IS_POS
							LD R3, ZERO_3400				;R3 <- Zero, signifies pos number
							BRnzp DONE2
IS_POS
							
							LD R2, CNEG_3400					;change check to check for negatives
							
							ADD R2, R2, R0					;check if neg number
BRnp IS_NEG
							LD R3, ONE_3400				;R3 <- One, signifies negative number
							BRnzp DONE2
IS_NEG
							LD R6, INPUT_VALIDATION_3400
							JSRR R6
							
							DONE2
							
; (3) Restore the registers that you backed up
LD R0, BACKUP_R0_3400
LD R1, BACKUP_R1_3400
LD R2, BACKUP_R2_3400
LD R4, BACKUP_R4_3400
LD R5, BACKUP_R5_3400
LD R6, BACKUP_R6_3400
LD R7, BACKUP_R7_3400
; (4) RETurn to where you came from
Ret

;------------------------
; Subroutine Data
;------------------------
ONE_3400		.FILL	#1
ZERO_3400		.FILL	#0
CPOS_3400		.FILL	#-43				;checks for pos
CNEG_3400		.FILL	#-45				;checks for neg

INPUT_VALIDATION_3400	.FILL	x3600
EXITOUT			.FILL	#-130

BACKUP_R0_3400	.BLKW	#1
BACKUP_R1_3400	.BLKW	#1
BACKUP_R2_3400	.BLKW	#1
BACKUP_R4_3400	.BLKW	#1
BACKUP_R5_3400	.BLKW	#1
BACKUP_R6_3400	.BLKW	#1
BACKUP_R7_3400	.BLKW	#1
.end

;----------------------------------------------------------------------------------------------------
; Subroutine Name: INPUT_VALIDATION
; Parameter (Register you are “passing” as a parameter): R0 - Number to check
														;R4 - <- First Range (inclusive)
														;R5 - <- Second Range(inclusive)
														;R2 - <- Address to jump to if error occurs
; Postcondition: Checks R0 to see if it is a valid character (between two specific ranges)
; Return Value: VOID

; How to call a function: LD R5, [SUBROUTINE NAME]
; Then JSRR R5
; In R5 is the address of your subroutine, with the subroutine name as your label
.orig x3600

;----------------------------------------------------------------------------------------------------

;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values

							ST R1, BACKUP_R1_3600
							ST R3, BACKUP_R3_3600
							ST R6, BACKUP_R6_3600
							ST R7, BACKUP_R7_3600
							
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
			
							ST R0, TEMP_3600
							ADD R0, R0, R4					;check start range
BRp	IS_ERROR
							LD R0, NEWLINE_3600
							OUT
							
							LEA R0, ERROR_3600
							PUTS
							
							LD R0, NEWLINE_3600
							OUT
							OUT
							
							LD R1, BACKUP_R1_3600			;back up registers if terminating
							LD R3, BACKUP_R3_3600
							LD R6, BACKUP_R6_3600
							LD R7, BACKUP_R7_3600
							
							JSRR R2							;go to specified address
IS_ERROR
						
							LD R0, TEMP_3600
							
							ADD R0, R0, R5					;check end range
BRn	IS_ERROR2
							LD R0, NEWLINE_3600
							OUT
							
							LEA R0, ERROR_3600
							PUTS
							
							LD R0, NEWLINE_3600
							OUT
							OUT
							
							LD R1, BACKUP_R1_3600			;back up registers if terminating
							LD R3, BACKUP_R3_3600
							LD R6, BACKUP_R6_3600
							LD R7, BACKUP_R7_3600
							
							JSRR R2							;go to specified address
IS_ERROR2
							LD R0, TEMP_3600				;restore R0
							RET
							
; (3) Restore the registers that you backed up

							LD R1, BACKUP_R1_3600
							LD R3, BACKUP_R3_3600
							LD R6, BACKUP_R6_3600
							LD R7, BACKUP_R7_3600
							
; (4) RETurn to where you came from

;------------------------
; Subroutine Data
;------------------------
							ERROR_3600			.stringz	"Invalid Character! Please reenter digit."
							NEWLINE_3600			.FILL	#10
							
							TEMP_3600			.BLKW	#1
							
							BACKUP_R1_3600	.BLKW	#1
							BACKUP_R3_3600	.BLKW	#1
							BACKUP_R6_3600	.BLKW	#1
							BACKUP_R7_3600	.BLKW	#1

;----------------------------------------------------------------------------------------------------
; Subroutine Name: DISPLAY_EQUATION

; Parameter (Register you are “passing” as a parameter): R1 <- Second Number to Display
														;R2 <- First Number to Display
														;R4 <- First Number Sign
														;R3 <- Second Number Sign
														;R5 <- Answer
														;R6 <- Answer sign
; Postcondition: Displays equation

; Return Value: VOID

.orig x3800
;----------------------------------------------------------------------------------------------------

;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R7, BACKUP_R7_3800
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
							ST R6, ANSWER_SIGN
							
							ADD R4, R4, #-1			;display first sign
							BRz NEGATIVE_SIGN
							
							LEA R0, Pos
							PUTS
							
							BRnzp DONE10
NEGATIVE_SIGN
							LEA R0, Minus
							PUTS
DONE10
							ST R1, EMPTY_3800		;save number in R1
							ADD R1, R2, #0			;switch parameter to R2
							LD R6, DISPLAY_NUMBER	;R6 <- Address; display first number in R1
							JSRR R6
							
							LEA R0, Asterisk
							PUTS
							
							ADD R3, R3, #-1			;display second sign
							BRz NEGATIVE_SIGN2
							
							LEA R0, Pos
							PUTS
							
							BRnzp DONE20
NEGATIVE_SIGN2
							LEA R0, Minus
							PUTS
DONE20
							
							ADD R1, R2, #0			;change parameter to second number
							LD R1, EMPTY_3800		;change parameter back to first number
							LD R6, DISPLAY_NUMBER	;R6 <- Address; display second number in R1
							JSRR R6
							
							LEA R0, Equals
							PUTS
							
							LD R6, ANSWER_SIGN
							ADD R6, R6, #-1			;check sign for answer
							BRz CHECK_AGAIN
							
							LEA R0, Pos
							PUTS
							
							BRnzp WHY
CHECK_AGAIN		
							LEA R0, Minus
							PUTS
WHY
							
							ADD R1, R5, #0			;output answer
							LD R6, DISPLAY_NUMBER
							JSRR R6
							
							
; (3) Restore the registers that you backed up
LD R7, BACKUP_R7_3800
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
Asterisk	.stringz	" * "
Equals		.stringz	" = "
Minus		.stringz	"-"
Pos			.stringz	"+"

ANSWER_SIGN			.BLKW		#1
EMPTY_3800			.BLKW		#1
DISPLAY_NUMBER		.FILL		x4000

BACKUP_R7_3800	.BLKW	#1

;----------------------------------------------------------------------------------------------------
; Subroutine Name: DISPLAY_NUMBER
; Parameter (Register you are “passing” as a parameter): R1 <- displaying this number
; Postcondition: Prints out R1
; Return Value: Void
.orig x4000
;----------------------------------------------------------------------------------------------------

;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R0, BACKUP_R0_4000
ST R2, BACKUP_R2_4000
ST R3, BACKUP_R3_4000
ST R4, BACKUP_R4_4000
ST R5, BACKUP_R5_4000
ST R6, BACKUP_R6_4000
ST R7, BACKUP_R7_4000
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
							ADD R2, R1, #0				;R2 <- value to change
							LD R3, DEC_COUNTER			;R3 <- Counter to display
							LD R4, NDEC_10000			;R4 <- Negative or pos number to add
							LD R5, ASCII_4000			;R5 <- offset
							LD R6, ZERO_4000					

AGAIN1
							ADD R2, R2, R4				
						BRn IS_NEGATIVE1
							
							ADD R3, R3, #1
							ADD R6, R6, #1				;PRINT OUT EVERY ZERO AFTER
							BRnzp AGAIN1
IS_NEGATIVE1
							ADD R6, R6, #0				;check flag and print 0 if needed
							BRnp PRINT_ZERO1
							
							ADD R3, R3, #0				;if counter is 0, skip
							BRz NEXTONE1
PRINT_ZERO1
							ADD R0, R3, #0
							ADD R0, R0, R5				;offset
							OUT
NEXTONE1
							
							LD R4, PDEC_10000
							LD R3, DEC_COUNTER			;reset counter
							ADD R2, R2, R4				;shift digits
							
							
AGAIN2
							LD R4, NDEC_1000			
							ADD R2, R2, R4				
						BRn IS_NEGATIVE2
							ADD R6, R6, #1				;PRINT OUT EVERY ZERO AFTER
							ADD R3, R3, #1
							BRnzp AGAIN2
IS_NEGATIVE2
							ADD R6, R6, #0				;check flag and print 0 if needed
							BRnp PRINT_ZERO2

							ADD R3, R3, #0				;if counter is 0, skip
							BRz NEXTONE2
PRINT_ZERO2
							ADD R0, R3, #0
							ADD R0, R0, R5				;offset
							OUT
NEXTONE2

							LD R4, PDEC_1000
							LD R3, DEC_COUNTER			;reset counter
							ADD R2, R2, R4				;shift digits

AGAIN3
							LD R4, NDEC_100
							ADD R2, R2, R4				
						BRn IS_NEGATIVE3
							ADD R6, R6, #1				;PRINT OUT EVERY ZERO AFTER
							ADD R3, R3, #1
							BRnzp AGAIN3
IS_NEGATIVE3
							ADD R6, R6, #0				;check flag and print 0 if needed
							BRnp PRINT_ZERO3

							ADD R3, R3, #0				;if counter is 0, skip
							BRz NEXTONE3
PRINT_ZERO3							
							ADD R0, R3, #0
							ADD R0, R0, R5				;offset
							OUT
NEXTONE3

							
							LD R4, PDEC_100
							LD R3, DEC_COUNTER			;reset counter
							ADD R2, R2, R4				;shift digits

AGAIN4
							LD R4, NDEC_10
							ADD R2, R2, R4				
						BRn IS_NEGATIVE4
							ADD R6, R6, #1				;PRINT OUT EVERY ZERO AFTER
							ADD R3, R3, #1
							BRnzp AGAIN4
IS_NEGATIVE4
							ADD R6, R6, #0				;check flag and print 0 if needed
							BRnp PRINT_ZERO4

							ADD R3, R3, #0				;if counter is 0, skip
							BRz NEXTONE4
PRINT_ZERO4	
							ADD R0, R3, #0
							ADD R0, R0, R5				;offset
							OUT
NEXTONE4

							
							LD R4, PDEC_10
							LD R3, DEC_COUNTER			;reset counter
							ADD R2, R2, R4				;shift digits
AGAIN5
							LD R4, NDEC_1
							ADD R2, R2, R4				
						BRn IS_NEGATIVE5
							ADD R6, R6, #1				;PRINT OUT EVERY ZERO AFTER
							ADD R3, R3, #1
							BRnzp AGAIN5
IS_NEGATIVE5
							
							ADD R0, R3, #0
							ADD R0, R0, R5				;offset
							OUT
							LD R4, PDEC_1
							LD R3, DEC_COUNTER			;reset counter
							ADD R2, R2, R4				;shift digits

; (3) Restore the registers that you backed up
LD R0, BACKUP_R0_4000
LD R2, BACKUP_R2_4000
LD R3, BACKUP_R3_4000
LD R4, BACKUP_R4_4000
LD R5, BACKUP_R5_4000
LD R6, BACKUP_R6_4000
LD R7, BACKUP_R7_4000
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
NDEC_10000		.FILL	#-10000
NDEC_1000		.FILL	#-1000
NDEC_100		.FILL	#-100
NDEC_10			.FILL	#-10
NDEC_1			.FILL	#-1

ZERO_4000		.FILL	#0

ASCII_4000		.FILL	#48

PDEC_10000		.FILL	#10000
PDEC_1000		.FILL	#1000
PDEC_100		.FILL	#100
PDEC_10			.FILL	#10
PDEC_1			.FILL	#1

DEC_COUNTER		.FILL	#0

BACKUP_R0_4000	.BLKW	#1
BACKUP_R2_4000	.BLKW	#1
BACKUP_R3_4000	.BLKW	#1
BACKUP_R4_4000	.BLKW	#1
BACKUP_R5_4000	.BLKW	#1
BACKUP_R6_4000	.BLKW	#1
BACKUP_R7_4000	.BLKW	#1

;----------------------------------------------------------------------------------------------------
; Subroutine Name: MULTIPLY
; Parameter (Register you are “passing” as a parameter): R1 <- Number 2
														;R2 <- Number 1
														;R4 <- First Number Sign
														;R3 <- Second Number Sign
; Postcondition: Multiplies two numbers and puts answer in R5
; Return Value: R5
.orig x4200
;----------------------------------------------------------------------------------------------------

;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R0, BACKUP_R0_4200
ST R3, BACKUP_R3_4200
ST R4, BACKUP_R4_4200
ST R7, BACKUP_R7_4200
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						
						ADD R6, R3, R4
						ADD R6, R6, #-1
						BRz ANSWER_NEGATIVE

						LD R6, ZERO_4200	;answer will be positive

						BRnzp VERY_DONE
ANSWER_NEGATIVE
						LD R6, ONE_4200		;answer till be negative
VERY_DONE
						
						ST R1, SECONDNUMB
						ST R2, FIRSTNUMB
						
						ADD R1, R1, #0		;Corner Case; check if either numbers are 0
						BRz CORNER_CASE
						ADD R2, R2, #0
						BRz CORNER_CASE
						
						NOT R1, R1			;make R1(second number) negative
						ADD R1, R1, #1
					
						ADD R5, R2, R1
						BRzp CHANGE_ORDER 
						ADD R5, R5, #0	
						BRn	CHANGE_ORDER2	
						
CHANGE_ORDER ;second number smaller
						LD R5, ZERO_4200
						LD R1, SECONDNUMB
						
						Multiply10					
							ADD R5, R5, R2
							BRn BADFLOW				;check for under/overflow
							
							ADD R1, R1, #-1			;decrement mcounter
						BRp Multiply10
END_Multiply10
						
						BRnzp FRICKING_FINISH
CHANGE_ORDER2 ;first number smaller
						LD R5, ZERO_4200
						LD R1, SECONDNUMB
						
						Multiply2					
							ADD R5, R5, R1
							BRn BADFLOW				;check for under/overflow
							
							ADD R2, R2, #-1			;decrement mcounter
						BRp Multiply2
END_Multiply2
						BRnzp FRICKING_FINISH
						
BADFLOW
													;UNDER/OVERFLOW ERROR
						ADD R6, R6, #-1				;check flag for what answer should have been
						BRz CHECK_NEG_AGAIN
						;OVERFLOW
						LEA R0, OVERFLOW
						PUTS
						
						LD R0, NEWLINE_4200
						OUT
						
						LD R6, RESTART
						JSRR R6
CHECK_NEG_AGAIN
						;UNDERFLOW
						LEA R0, UNDERFLOW
						PUTS
						
						LD R0, NEWLINE_4200
						OUT
						
						LD R6, RESTART
						JSRR R6
		
CORNER_CASE
						LD R5, ZERO_4200
						LD R6, ZERO_4200
						
FRICKING_FINISH
						LD R1, SECONDNUMB
						LD R2, FIRSTNUMB
; (3) Restore the registers that you backed up
LD R0, BACKUP_R0_4200
LD R3, BACKUP_R3_4200
LD R4, BACKUP_R4_4200
LD R7, BACKUP_R7_4200
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
ZERO_4200		.FILL	#0 ;pos
ONE_4200		.FILL	#1 ;neg
NEWLINE_4200	.FILL	#10

FIRSTNUMB		.BLKW	#5
SECONDNUMB		.BLKW	#5

ANSWER_SIGN_4200	.BLKW	#1

CHECK1			.BLKW	#1
CHECK2			.BLKW	#1

OVERFLOW		.stringz	"Overflow!!! Please try again."
UNDERFLOW		.stringz	"Underflow!!! Please try again."
RESTART			.FILL		x3000

BACKUP_R0_4200	.BLKW	#1
BACKUP_R3_4200	.BLKW	#1
BACKUP_R4_4200	.BLKW	#1
BACKUP_R7_4200	.BLKW	#1

.end
