;=================================================
; Name: Feng, Rica
; Login id: rfeng001	
;
; Assignment name: assn8.asm
; Lab section: 22
; TA: Aditya Tammewar
;
; I hereby certify that the contents of this file
; are ENTIRELY my own original work.
;=================================================
.orig x3000
;------------------------------------------------------------------
;INSTRUCTIONS
;------------------------------------------------------------------
	LD R5, SUB_ROUTINE_ARRAY			;following code fills array with subroutine address
	
	LD R4, ALL_MACHINES_BUSY
	STR R4, R5, #0
	ADD R5, R5, #1
	
	LD R4, ALL_MACHINES_FREE
	STR R4, R5, #0
	ADD R5, R5, #1
	
	LD R4, NUM_BUSY_MACHINES
	STR R4, R5, #0
	ADD R5, R5, #1
	
	LD R4, NUM_FREE_MACHINES
	STR R4, R5, #0
	ADD R5, R5, #1
	
	LD R4, MACHINE_STATUS
	STR R4, R5, #0
	ADD R5, R5, #1
	
	LD R4, FIRST_FREE	
	STR R4, R5, #0
	ADD R5, R5, #1
	
	ALWAYS_RUN
		LD R6, SUB_MENU
		JSRR R6
		
		ST R1, STORE_CHOICE
		
		LD R4, CQUIT				;R4 <- Check statements
		ADD R0, R4, R1				;check if choice 7, if so then quit
		BRz QUIT
		
		LD R4, C5
		ADD R0, R4, R1
		BRnp NOT_CHOICE5			;run extra code if choice 5 (Ask user for machine to check)
		
		LEA R0, R5ASK
		PUTS
		
		LD R6, GET_INPUT			;get a number up to 2 digits and store in R1
		JSRR R6
		
		ST R1, STOREC5
		
	NOT_CHOICE5
		
		LD R5, SUB_ROUTINE_ARRAY	;reset array
		ADD R5, R5, #-1				;array should be one less so loop works correctly
		
		LD R1, STORE_CHOICE
		
		GET_CHOICE					;loop will go to correct subroutine in memory
			ADD R5, R5, #1
			ADD R1, R1, #-1			;R1 <- choice from menu
			BRp GET_CHOICE
		END_GET_CHOICE
		
		LD R1, STOREC5
									;
		LDR R6, R5, #0				;R6 <-address of correct subroutine
		JSRR R6						;run subroutine if not choice 7
		
		LD R3, STORE_CHOICE			;based on the choice, code will choose specific response
		
		LD R4, C1
		ADD R4, R3, R4
		BRz RESPONSE1

		LD R4, C2
		ADD R4, R3, R4
		BRz RESPONSE2

		LD R4, C3
		ADD R4, R3, R4
		BRz RESPONSE3
		
		LD R4, C4
		ADD R4, R3, R4
		BRz RESPONSE4
		
		LD R4, C5
		ADD R4, R3, R4
		BRz RESPONSE5
		
		LD R4, C6
		ADD R4, R3, R4
		BRz RESPONSE6
		
	RESPONSE1							;response 1
		ADD R2, R2, #0
		BRz ALL_NOT_BUSY
		
		LEA R0, R1T
		PUTS
		
		BR ALWAYS_RUN
	ALL_NOT_BUSY
		
		LEA R0, R1F
		PUTS
		
		BR ALWAYS_RUN
		
	RESPONSE2							;response 2
		ADD R2, R2, #0
		BRz ALL_NOT_FREE
		
		LEA R0, R2T
		PUTS
		
		BR ALWAYS_RUN
	ALL_NOT_FREE
		
		LEA R0, R2F
		PUTS
		
		BR ALWAYS_RUN
		
	RESPONSE3							;response 3
		LD R0, NEWLINE
		OUT
		
		ADD R1, R2, #0					;set up paremeter to display number
		LD R2, DISPLAY_NUMBER			;display number
		JSRR R2
		
		LEA R0, R3B
		PUTS
		
		BR ALWAYS_RUN
		
	RESPONSE4							;response 4
		LD R0, NEWLINE
		OUT
		
		ADD R1, R2, #0					;set up paremeter to display number
		LD R2, DISPLAY_NUMBER			;display number
		JSRR R2
		
		LEA R0, R4B
		PUTS
		
		BR ALWAYS_RUN
		
	RESPONSE5							;response 5
		LD R1, STOREC5
		LEA R0, R5A
		PUTS
		
		LD R6,	DISPLAY_NUMBER
		JSRR R6						
		
		ADD R2, R2, #0					;check R2 if machine is busy or free
		BRnp MACHINE_FREE
		
		LEA R0, R5T
		PUTS
		BR ALWAYS_RUN
		
	MACHINE_FREE
		LEA R0, R5F
		PUTS
		BR ALWAYS_RUN
		
	RESPONSE6							;response 6
		LEA R0, R6A
		PUTS
	
		ADD R1, R2, #0					;copy R2 to R1
		ADD R0, R1, #1					;check if R1 is negative
		BRz NONE_FREE
		
		LD R6, DISPLAY_NUMBER
		JSRR R6
		BR ALWAYS_RUN
		
	NONE_FREE
		LEA R0, R6N
		PUTS
		
		BR ALWAYS_RUN
QUIT

	LEA R0, GOODBYE
	PUTS
	
	HALT
	;------------------------------------------------------------------
	;LOCAL DATA
	;------------------------------------------------------------------
	C1				.FILL	#-1
	C2				.FILL	#-2
	C3				.FILL	#-3
	C4				.FILL	#-4
	C5				.FILL	#-5
	C6				.FILL	#-6
	CQUIT			.FILL	#-7
	ONE				.FILL	#1
	ASCII			.FILL	#48
	NEWLINE			.FILL	#10
	SUB_MENU			.FILL	x3300
	ALL_MACHINES_BUSY	.FILL	x3600
	ALL_MACHINES_FREE	.FILL	x3800
	NUM_BUSY_MACHINES	.FILL	x4000
	NUM_FREE_MACHINES	.FILL	x4200
	MACHINE_STATUS		.FILL	x4400
	FIRST_FREE			.FILL	x4600
	DISPLAY_NUMBER		.FILL	x4800
	GET_INPUT			.FILL	x5000
	SUB_ROUTINE_ARRAY	.FILL	x6000
	
	STOREC5			.BLKW	#1
	STORE_MACHINE	.BLKW	#1
	STORE_CHOICE	.BLKW	#1
	
	GOODBYE			.stringz	"\nBye!\n"
	
	R1T				.stringz	"\nAll machines busy!\n"
	R1F				.stringz	"\nAll machines not busy.\n"
	
	R2T				.stringz	"\nAll machines free!\n"
	R2F				.stringz	"\nAll machines not free.\n"
	
	R3B				.stringz	" busy machines.\n"
	R4B				.stringz	" free machines.\n"
	
	R5ASK			.stringz	"\nWhich machine to check?(0-15): "
	R5A				.stringz	"\nMachine "
	R5T				.stringz	" is busy.\n"
	R5F				.stringz	" is free.\n"
	
	R6A				.stringz	"\nFirst free machine: "
	R6N				.stringz	"NA\n"
	
	C5COUNTER		.FILL	#2
	CNEWLINE		.FILL	#-10
	
	;------------------------------------------------------------------
	;REMOTE DATA
	;------------------------------------------------------------------
;-----------------------------------------------------------------------------------------------------------------
; Subroutine: MENU
; Inputs: None
; Postcondition: The subroutine has printed out a menu with numerical options, allowed the
; user to select an option, and returned the selected option.
; Return Value (R1): The option selected: #1, #2, #3, #4, #5, #6 or #7
; no other return value is possible
;-----------------------------------------------------------------------------------------------------------------
.orig x3300
;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R0, BACKUP_R0_3300
ST R4, BACKUP_R4_3300
ST R5, BACKUP_R5_3300
ST R6, BACKUP_R6_3300
ST R7, BACKUP_R7_3300
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						BR RESTART_MENU
						RESTART_AGAIN
							LEA R0, INVALID_3300
							PUTS
						RESTART_MENU
							LD R5, OFFSET_3300
							LD R6, CSEVEN_3300
						
							LEA R0, MENU_CALL
							PUTS
							
							LEA R0, CHOICE_3300
							PUTS
							
							GETC
							OUT
							
							ADD R4, R0, R5		;Check if valid
							BRnz RESTART_AGAIN
							
							ADD R0, R0, R5		;offset
							
							ADD R4, R6, R0		;Check if valid
							BRp RESTART_AGAIN
						
							ADD R1, R0, #0		;copy number to R1
; (3) Restore the registers that you backed up
LD R0, BACKUP_R0_3300
LD R4, BACKUP_R4_3300
LD R5, BACKUP_R5_3300
LD R6, BACKUP_R6_3300
LD R7, BACKUP_R7_3300
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
BACKUP_R0_3300	.BLKW	#1
BACKUP_R4_3300	.BLKW	#1
BACKUP_R5_3300	.BLKW	#1
BACKUP_R6_3300	.BLKW	#1
BACKUP_R7_3300	.BLKW	#1

CSEVEN_3300		.FILL		#-7
OFFSET_3300		.FILL		#-48
CHOICE_3300		.stringz	"Enter choice: "
INVALID_3300	.stringz	"\nInvalid response!\n"
MENU_CALL		.stringz	 "\n**********************\n* The Busyness Server *\n**********************\n1. Check to see whether all machines are busy\n2. Check to see whether all machines are free\n3. Report the number of busy machines\n4. Report the number of free machines\n5. Report the status of machine n\n6. Report the number of the first available machine\n7. Quit\n"


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: ALL_MACHINES_BUSY
; Inputs: None
; Postcondition: The subroutine has returned a value indicating whether all machines are busy
; Return value (R2): 1 if all machines are busy, 0 otherwise
;-----------------------------------------------------------------------------------------------------------------
.orig x3600
; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R6, BACKUP_R6_3600
ST R5, BACKUP_R6_3600
ST R7, BACKUP_R7_3600
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						LD R5, BUSYNESS_3600
						LDR R5, R5, #0
						LD R6, MASK_3600
						
						AND R6, R5, R6			;check if all registers are zero
						BRz ALL_BUSY
						
						LD R2, ZERO_3600
						
						BR NOT_ALL_BUSY
					ALL_BUSY
						LD R2, ONE_3600
					NOT_ALL_BUSY
; (3) Restore the registers that you backed up
LD R5, BACKUP_R5_3600
LD R6, BACKUP_R6_3600
LD R7, BACKUP_R7_3600
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
ONE_3600		.FILL	#1
ZERO_3600		.FILL	#0
BUSYNESS_3600	.FILL	x5200
MASK_3600		.FILL	xFFFF

BACKUP_R5_3600	.BLKW	#1
BACKUP_R6_3600	.BLKW	#1
BACKUP_R7_3600	.BLKW	#1


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: ALL_MACHINES_FREE
; Inputs: None
; Postcondition: The subroutine has returned a value indicating whether all machines are free
; Return value (R2): 1 if all machines are free, 0 otherwise
;-----------------------------------------------------------------------------------------------------------------
.orig x3800
; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R5, BACKUP_R5_3800
ST R6, BACKUP_R6_3800
ST R7, BACKUP_R7_3800
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						LD R5, BUSYNESS_3800
						LDR R5, R5, #0
						
						NOT R6, R5					;not R5 to check if 0s
						BRz ALL_FREE
						
						LD R2, ZERO_3800
						
						BR DONE_3800
					ALL_FREE
						LD R2, ONE_3800
					DONE_3800
; (3) Restore the registers that you backed up
LD R5, BACKUP_R5_3800
LD R6, BACKUP_R6_3800
LD R7, BACKUP_R7_3800
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
ONE_3800		.FILL	#1
ZERO_3800		.FILL	#0
BUSYNESS_3800	.FILL	x5200

BACKUP_R5_3800	.BLKW	#1
BACKUP_R6_3800	.BLKW	#1
BACKUP_R7_3800	.BLKW	#1


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: NUM_BUSY_MACHINES
; Inputs: None
; Postcondition: The subroutine has returned the number of busy machines.
; Return Value (R2): The number of machines that are busy
;-----------------------------------------------------------------------------------------------------------------
.orig x4000
; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R1, BACKUP_R1_4000
ST R3, BACKUP_R3_4000
ST R7, BACKUP_R7_4000
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						LD R1, BUSYNESS_4000
						LDR R1, R1, #0				;get number to check into R1
						
						LD R2, ZERO_4000			;R2 <- Counter for number of busy machines
						LD R3, COUNTER_4000			;R3 <- Counter, loop 16 times
			
						FIND_BUSY				;Find number of busy machines
							ADD R1, R1, #0			
							BRn IS_FREE
								ADD R2, R2, #1			;if number is positive, add 1 to counter
							IS_FREE
							
							ADD R1, R1, R1			;multiply number by 2
							ADD R3, R3, #-1			;decrement counter
							BRp FIND_BUSY
						END_FIND_BUSY

; (3) Restore the registers that you backed up
LD R1, BACKUP_R1_4000
LD R3, BACKUP_R3_4000
LD R7, BACKUP_R7_4000
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
ZERO_4000		.FILL	#0
COUNTER_4000	.FILL	#16
BUSYNESS_4000	.FILL	x5200

BACKUP_R1_4000	.BLKW	#1
BACKUP_R3_4000	.BLKW	#1
BACKUP_R7_4000	.BLKW	#1


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: NUM_FREE_MACHINES
; Inputs: None
; Postcondition: The subroutine has returned the number of free machines
; Return Value (R2): The number of machines that are free 
;-----------------------------------------------------------------------------------------------------------------
.orig x4200
; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R1, BACKUP_R1_4200
ST R3, BACKUP_R3_4200
ST R7, BACKUP_R7_4200
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						LD R1, BUSYNESS_4200
						LDR R1, R1, #0				;get number to check into R1
						
						LD R2, ZERO_4200			;R2 <- Counter for number of free machines
						LD R3, COUNTER_4200			;R3 <- Counter, loop 16 times
			
						FIND_FREE				;Find number of free machines
							ADD R1, R1, #0			
							BRzp IS_BUSY5
								ADD R2, R2, #1			;if number is positive, add 1 to counter
							IS_BUSY5
							
							ADD R1, R1, R1			;multiply number by 2
							ADD R3, R3, #-1			;decrement counter
							BRp FIND_FREE
						END_FIND_FREE

; (3) Restore the registers that you backed up
LD R1, BACKUP_R1_4200
LD R3, BACKUP_R3_4200
LD R7, BACKUP_R7_4200
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
ZERO_4200		.FILL	#0
COUNTER_4200	.FILL	#16
BUSYNESS_4200	.FILL	x5200

BACKUP_R1_4200	.BLKW	#1
BACKUP_R3_4200	.BLKW	#1
BACKUP_R7_4200	.BLKW	#1


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: MACHINE_STATUS
; Input (R1): Which machine to check
; Postcondition: The subroutine has returned a value indicating whether the machine indicated
; by (R1) is busy or not.
; Return Value (R2): 0 if machine (R1) is busy, 1 if it is free
;-----------------------------------------------------------------------------------------------------------------
.orig x4400
; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R4, BACKUP_R4_4400
ST R3, BACKUP_R3_4400
ST R7, BACKUP_R7_4400
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						LD R4, BUSYNESS_4400
						LDR R4, R4, #0				;get number to check into R1
						
						LD R2, ZERO_4400			;R2 <- if 1, machine busy, if 0, machine free
						LD R3, COUNTER_4400			;R3 <- Counter, loop 16 times
			
						FIND_MACHINE				;Find number of free machines
							ADD R2,	R3, R1			;check if correct machine 
							BRnp NOT_CORRECT
							
							ADD R4, R4, #0			
							BRzp IS_BUSY
								ADD R2, R2, #1
								BR IM_DONE			
							IS_BUSY
								ADD R2, R2, #0
							BR IM_DONE
							
						NOT_CORRECT
							ADD R4, R4, R4			;multiply number by 2
							ADD R3, R3, #1			;increment counter
							BR FIND_MACHINE
						END_FIND_MACHINE
					
					IM_DONE
; (3) Restore the registers that you backed up
LD R4, BACKUP_R4_4400
LD R3, BACKUP_R3_4400
LD R7, BACKUP_R7_4400
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
ZERO_4400		.FILL	#0
ONE_4400		.FILL	#1
COUNTER_4400	.FILL	#-15
BUSYNESS_4400	.FILL	x5200

BACKUP_R4_4400	.BLKW	#1
BACKUP_R3_4400	.BLKW	#1
BACKUP_R7_4400	.BLKW	#1


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: FIRST_FREE
; Inputs: None
; Postcondition: 
; The subroutine has returned a value indicating the lowest numbered free machine
; Return Value (R2): the number of the free machine
;-----------------------------------------------------------------------------------------------------------------
.orig x4600
; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R3, BACKUP_R3_4600
ST R4, BACKUP_R4_4600
ST R5, BACKUP_R5_4600
ST R7, BACKUP_R7_4600
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						LD R4, BUSYNESS_4600
						LDR R4, R4, #0				;get number to check into R1
						
						LD R5, F_COUNTER_4600	
						
						LD R2, ONE_4600			;R2 <- number of first free machine, -1 if all busy
						ST R2, FIRST_FREE_4600			;default answer is
						
						LD R3, COUNTER_4600			;R3 <- Counter, loop 16 times
			
						FIND_FIRST_FREE			;Find number of free machines
							ADD R4, R4, #0			
							BRzp IS_BUSY3
								ST R3, FIRST_FREE_4600	
							IS_BUSY3
							
							ADD R4, R4, R4			;multiply number by 2
							ADD R3, R3, #1			;increment counter
							
							ADD R5, R5, #-1
							BRp FIND_FIRST_FREE
						END_FIND_FIRST_FREE
				
						;LD R3, NEG_ONE_4600
						LD R2, FIRST_FREE_4600
						
						;ADD R3, R3, R2
						;BRz NONE_FREE2
						
						NOT R2, R2			;turn positive
						ADD R2, R2, #1
					;NONE_FREE2
; (3) Restore the registers that you backed up
LD R3, BACKUP_R3_4600
LD R4, BACKUP_R4_4600
LD R5, BACKUP_R5_4600
LD R7, BACKUP_R7_4600
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
FIRST_FREE_4600		.BLKW	#1

F_COUNTER_4600	.FILL	#16
ONE_4600		.FILL	#1
ZERO_4600		.FILL	#0
NEG_ONE_4600	.FILL	#-1
COUNTER_4600	.FILL	#-15
BUSYNESS_4600	.FILL	x5200

BACKUP_R3_4600	.BLKW	#1
BACKUP_R4_4600	.BLKW	#1
BACKUP_R5_4600	.BLKW	#1
BACKUP_R7_4600	.BLKW	#1
;----------------------------------------------------------------------------------------------------
; Subroutine Name: DISPLAY_NUMBER
; Parameter (Register you are “passing” as a parameter): R1 <- displaying this number
; Postcondition: Prints out R1
; Return Value: Void
.orig x4800
;----------------------------------------------------------------------------------------------------

;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values
ST R0, BACKUP_R0_4800
ST R2, BACKUP_R2_4800
ST R3, BACKUP_R3_4800
ST R4, BACKUP_R4_4800
ST R5, BACKUP_R5_4800
ST R6, BACKUP_R6_4800
ST R7, BACKUP_R7_4800
; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
							ADD R2, R1, #0				;R2 <- value to change
							LD R3, DEC_COUNTER			;R3 <- Counter to display
							LD R4, NDEC_10000			;R4 <- Negative or pos number to add
							LD R5, ASCII_4800			;R5 <- offset
							LD R6, ZERO_4800					

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
LD R0, BACKUP_R0_4800
LD R2, BACKUP_R2_4800
LD R3, BACKUP_R3_4800
LD R4, BACKUP_R4_4800
LD R5, BACKUP_R5_4800
LD R6, BACKUP_R6_4800
LD R7, BACKUP_R7_4800
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

ZERO_4800		.FILL	#0

ASCII_4800		.FILL	#48

PDEC_10000		.FILL	#10000
PDEC_1000		.FILL	#1000
PDEC_100		.FILL	#100
PDEC_10			.FILL	#10
PDEC_1			.FILL	#1

DEC_COUNTER		.FILL	#0

BACKUP_R0_4800	.BLKW	#1
BACKUP_R2_4800	.BLKW	#1
BACKUP_R3_4800	.BLKW	#1
BACKUP_R4_4800	.BLKW	#1
BACKUP_R5_4800	.BLKW	#1
BACKUP_R6_4800	.BLKW	#1
BACKUP_R7_4800	.BLKW	#1

;----------------------------------------------------------------------------------------------------
; Subroutine Name: GET_INPUT
; Parameter (Register you are “passing” as a parameter): None
; Postcondition: Takes input, up to two digits, and inserts the number into R1
; Return Value: R1
.orig x5000
;----------------------------------------------------------------------------------------------------

;---------------------------------
; Subroutine Instructions
;---------------------------------

; (1) Backup R7 and all registers that this subroutine changes except Return Values

ST R0, BACKUP_R0_5000
ST R2, BACKUP_R2_5000
ST R3, BACKUP_R3_5000
ST R4, BACKUP_R4_5000
ST R6, BACKUP_R6_5000
ST R7, BACKUP_R7_5000

; (2) Perform whatever algorithm(s) this subroutine is suppose to perform
						BR SKIP
						GET_AGAIN
							LEA R0, WRONG
							PUTS
							
						SKIP
							LD R2, CNEWLINE_5000
							LD R3, MULT_COUNTER
							LD R4, OFFSET_5000
							LD R6, ZERO_5000
							
							GETC							;get first digit
							OUT
							
							LD R6, CHECK1					;check first char if 0-9
							ADD R6, R6, R0
							BRnz GET_AGAIN
							
							LD R6, CHECK2
							ADD R6, R6, R0
							BRzp GET_AGAIN
							
							ADD R0, R0, R4					;offset
							ADD R1, R0, #0					;copy number to R1
			
							GETC
							
							ADD R2, R2, R0					;check if newline
							BRz IS_NEWLINE
							
							OUT
							
							LD R6, CHECK1					;check second char if 0-9
							ADD R6, R6, R0
							BRnz GET_AGAIN
							
							LD R6, CHECK2
							ADD R6, R6, R0
							BRzp GET_AGAIN
							
							ADD R1, R3, #0					;change R1 to 10 if second char valid
										
							ADD R0, R0, R4
							ADD R1, R0, R1					
							
							ADD R1, R1, #0
							BRn GET_AGAIN
							
							LD R6, CHECKA
							ADD R6, R6, R1
							BRzp GET_AGAIN
					IS_NEWLINE
; (3) Restore the registers that you backed up
LD R0, BACKUP_R0_5000
LD R2, BACKUP_R2_5000
LD R3, BACKUP_R3_5000
LD R4, BACKUP_R4_5000
LD R6, BACKUP_R6_5000
LD R7, BACKUP_R7_5000
; (4) RETurn to where you came from
Ret
;------------------------
; Subroutine Data
;------------------------
CNEWLINE_5000	.FILL	#-10
OFFSET_5000		.FILL	#-48
MULT_COUNTER	.FILL	#10
ZERO_5000		.FILL	#0

WRONG			.stringz	"\nInvalid Input! Try again.\n"

CHECK1		.FILL	#-47
CHECK2		.FILL	#-58
CHECKA		.FILL	#-16

BACKUP_R0_5000	.BLKW	#1
BACKUP_R2_5000	.BLKW	#1
BACKUP_R3_5000	.BLKW	#1
BACKUP_R4_5000	.BLKW	#1
BACKUP_R6_5000	.BLKW	#1
BACKUP_R7_5000	.BLKW	#1

;example in specs
			.orig x5200
BUSYNESS	.FILL	x6A13
