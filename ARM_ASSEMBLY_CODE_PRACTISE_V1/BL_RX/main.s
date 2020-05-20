
TEMP 		EQU 		100
	

RAM_ADDR    EQU 0x20000000
	
			AREA mycode,CODE,READONLY
			ENTRY
			EXPORT		__main

__main		
			LDR		R0,=RAM_ADDR
Again		MOV		R1,#0x55
			STRB	R1,[R0]
			BL		Delay
			MOV		R1,#0xAA
			STRB	R1,[R0]
			BL		Delay
			B		Again

Delay		
			LDR		R3,=5
L1			SUBS	R3,R3,#1
			BNE     L1   ;run while z!=0
			BX		LR
			
loop			B		loop
			ALIGN
			END