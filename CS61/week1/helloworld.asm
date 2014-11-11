.ORIG x3000

;Instructions
	LEA R0, MSG_TO_PRINT	;RO is the location of label MSG_TO_PRINT
	PUTS					;Prints string defined at MSG_TO_PRINT
	
	HALT					;Terminates

;Local Data
	MSG_TO_PRINT	.STRINGZ	"Hello world!!!\n"	
	
	;store each character ('h','e','l'...) in address labaled
	;MSG_TO_PRINT in the same order followed by #0 at the end to mark
	;the end of the string

	
	
	
.END
