


			AREA eg3,CODE,READONLY
			ENTRY
			EXPORT		__main

__main

			ADRL 	R4,vals   ;R4 POINTER POINT TO VALS AREA
			LDR		R1,[R4,#Q]
			LDR		R2,[R4,#R]
			LDR		R3,[R4,#S]
			
			ADD		R5,R1,R2
			ADD		R5,R5,R3
STOP        B		STOP
			
			
			
			
P			EQU			0
Q			EQU			4
R			EQU			8
S			EQU			12

			AREA eg3,DATA,READ
				
vals		SPACE     	4
			DCD			2
			DCD			10
			DCD			12
				
			END
