

			AREA div,CODE,READONLY
			ENTRY
			EXPORT	__main
__main
			LDR		R0,=2010
			MOV		R1,#10
			MOV		R2,#0
			
again		CMP		R0,R1
			BLO		stop
			SUBS	R0,R0,R1
			ADD		R2,R2,#1
			B		again


stop		B		stop
			ALIGN
			END