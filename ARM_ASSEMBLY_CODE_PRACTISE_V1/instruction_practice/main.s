
TEMP 		EQU 		100
	
	AREA data,DATA,READONLY
myport		DCD			100
	
			AREA mycode,CODE,READONLY
			ENTRY
			EXPORT		__main

__main		
			 MOV 	R0,#TEMP ;R0 = Temp
			 LDR 	R1,=myport ;port address
OVER 		 LDRB 	R2,[R1] ;load R2 from myport
			 TEQ 	R2,R0 ;is it 100?
			 BEQ    just
			 BNE 	OVER ;keep checking
just		
			LDR		R0,=200
			 
loop			B		loop
			ALIGN
			END