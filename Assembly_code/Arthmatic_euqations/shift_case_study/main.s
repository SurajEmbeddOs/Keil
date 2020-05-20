
;(A+8E+7C-27)/4
;let A=25,E=19,C=99 
A		RN		R0
E		RN		R1
C		RN		R2
Sum		RN		R4

			AREA cmeqe,CODE,READONLY
			ENTRY
			EXPORT		__main

__main
			MOV		A,#25
			MOV		E,#15
			MOV		C,#17
			MOV		Sum,#0
			
			ADD		Sum,A
			ADD		Sum,E,LSL #3
			MOV		R7,#7
			MLA		Sum,C,R7,Sum
			SUB		Sum,Sum,#20
			MOV		Sum,Sum,ASR #2  ;Divide total by four
			
			
stop		B	stop
			ALIGN
			END
				

