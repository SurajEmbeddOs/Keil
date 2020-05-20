


			AREA MyDATA,DATA,READONLY

P			SPACE			4	;Reserve 4 bytes of memory
Q			DCD				2   ;create variable q with intial value 0x00000002
R			DCD				10
S			DCD				12

			AREA myCode,CODE,READONLY
			ENTRY
			EXPORT		__main

__main
			LDR 	R1,Q
			LDR		R2,R
			LDR		R3,S
			
			ADD		R0,R1,R2
			ADD		R0,R0,R3
			
Stop		B		Stop
			END
			