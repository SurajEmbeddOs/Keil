 
 
 
			AREA myCode,CODE,READONLY
			ENTRY
			EXPORT		__main

__main
			LDR 	R0,=SIGN_BYTE
			MOV		R1,#0
			MOV		R2,#9
			
L1			LDRSH	R4,[R0]
			ADD		R1,R1,R4
			ADD		R0,R0,#2
			SUBS	R2,R2,#1
			BNE		L1
			
stop		B		stop
			
				

SIGN_BYTE	DCW   +300,-9,+12,-14,+2,+3,+4,+6,+9
			ALIGN
			END