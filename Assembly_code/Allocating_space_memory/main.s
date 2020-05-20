

			AREA myCode,CODE,READONLY
			ENTRY
			EXPORT	__main

__main
			LDR		R0,=A
			MOV		R1,#5
			STR		R1,[R0]
			
			LDR		R0,=D
			MOV		R1,#10
			STR		R1,[R0]
			
			LDR		R0,=E
			MOV		R1,#20
			STR		R1,[R0]
LOOP		B		LOOP



			AREA	myData,DATA,READWRITE
			;Allocating space in SRAM

A			SPACE	4
D			SPACE	4
E			SPACE	4
	
			END