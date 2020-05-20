

			AREA fact,CODE,READONLY
			ENTRY
			EXPORT		__main

__main
			MOV		R6,#10
			MOV		R7,#1

loop
			CMP		R6,#0
			ITTT	GT
			MULGT	R7,R6,R7
			SUBGT	R6,R6,#1
			BGT		loop
stop		B		stop
			END
						