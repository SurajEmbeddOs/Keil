

; find max number amonge them 25,65,28,68,95,12

Pointer			RN		R0
Count			RN		R1
MAX				RN		R3
Next			RN		R4


			AREA myData,DATA,READONLY
MyDATA		DCD		0x25,0x65,0x28,0x68,0x95,0x25
	
	
			AREA myCode,CODE,READONLY
			ENTRY
			EXPORT		__main


__main
			LDR		Pointer,=MyDATA
			MOV		MAX,#0
			MOV		Count,#6
			
Again		LDR		Next,[Pointer]
			CMP		MAX,Next   ;MAX-Next ;		
			BHS     jump	 ;if c=1 jump
			MOV		MAX,Next
jump		ADD		Pointer,Pointer,#4
			SUBS	Count,Count,#1
			
			BNE		Again
			
loop        B		loop

			ALIGN
			END
			