



			AREA myCode,CODE,READONLY
			ENTRY
			EXPORT		__main

__main

;Check zero flag
;			MOV		R0,#4
;			MOV		R1,#2
;			MOV		R3,#4
;			
;			SUBS	R4,R0,R1
;			SUBS	R4,R0,R3

;Check cary flag
;			LDR		R0,=0xFAB14254
;			LDR		R1,=0xFAB14254
;			
;			MOV		R2,#0x34
;			MOV		R3,#0x35
;			
;			ADDS	R5,R2,R3
;			ADC		R6,R2,R3
;Check overload flag	
			LDR		R1,=1000000000
			LDR		R2,=2000000000
			LDR		R3,=3000000000
			LDR		R4,=4000000000
			LDR		R5,=4100000000
			
			MOV		R8,#0
			MOV		R9,#0
			
			ADDS	R8,R8,R0
			ADC		R9,R9,#0
			
			ADDS	R8,R8,R1
			ADC		R9,R9,#0

			ADDS	R8,R8,R3
			ADC		R9,R9,#0
			
			ADDS	R8,R8,R4
			ADC		R9,R9,#0
			
			ADDS	R8,R8,R5
			ADC		R9,R9,#0
			
stop		B		stop
			ALIGN
			
			END