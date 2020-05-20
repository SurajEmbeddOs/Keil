
Stack_Top 	EQU     0x2001BFFC

			AREA mycode,CODE,READONLY
			ENTRY
			EXPORT		__main
			
__main
			LDR		 R13,=Stack_Top ;load SP 
			LDR		 R0,=0x125 ;R0 = 0x125 
			LDR		 R1,=0x144 ;R1 = 0x144 
			MOV		 R2,#0x56 ;R2 = 0x56 
			BL 		MY_SUB ;call a subroutine ADD R3,R0,R1
			
			;R3 = R0 + R1 = 0x125 + 0x144 = 0x269 
			ADD		 R3,R3,R2 ;R3 = R3 + R2 = 0x269 + 0x56 = 0x2BF 
HERE		 B 		HERE ;stay here


MY_SUB
			;save R0, R1, and R2 on stack ;before they are used by a loop 
			STR		 R0,[R13] ;save R0 on stack 
			SUB		 R13,R13,#4 ;R13 = R13 - 4, to decrement the stack pointer 
			STR		 R1,[R13] ;save R1 on stack 
			SUB		 R13,R13,#4 ;R13 = R13 - 4, to decrement the stack pointer
			STR 	R2,[R13] ;save R2 on stack 
			SUB 	R13,R13,#4 ;R13 = R13 - 4, to decrement the stack pointer
			
			MOV		 R0,#0 ;R0 = 0 
			MOV		 R1,#0 ;R1 = 0 
			MOV		 R2,#0 ;R2 = 0
			
			
			ADD		 R13,R13,#4 ;R13 = R13 + 4 to increment the stack pointer 
			LDR		 R2,[R13] ;restore R2 from stack 
			ADD		 R13,R13,#4 ;R13 = R13 + 4 to increment the stack pointer 
			LDR		 R1,[R13] ;restore R1 from stack 
			ADD		 R13,R13,#4 ;R13 = R13 + 4 to increment the stack pointer 
			LDR		 R0,[R13] ;restore R0 from stack BX LR ;return to caller
			
			BX		LR		
			
			ALIGN
			END
			
			
			
			
			
			
			
			
			
			
			
			
			
			