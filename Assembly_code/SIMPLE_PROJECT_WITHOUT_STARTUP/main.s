
Stack			EQU		0x00000100
	
				AREA STACK,NOINIT,READWRITE,ALIGN=3
				
STACKMEM		SPACE		Stack
	
				AREA RESET,DATA,READONLY
				EXPORT	__Vectors

__Vectors
				DCD		STACKMEM +Stack
				DCD		Reset_Handler
				ALIGN
				
				AREA simple_project,CODE,READONLY,ALIGN=2
				ENTRY
				EXPORT	Reset_Handler

Reset_Handler
				MOV		R3,#0x1234
				MOV		R4,#0x1234
				
				ADD		R5,R3,R4
LOOP			B       LOOP
				ALIGN
				END