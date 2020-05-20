	
	
			AREA mycode,CODE,READONLY
			ENTRY
			EXPORT		__main

__main

			BL		prog_set_7


stop			B			stop

					
prog_set_1 
			
			MOV		 R1,#10     ;R1 = 10
			MOV		 R2,#12     ;R2 = 12
			CMP		 R2,R1      ;compare 12 with 10, Z = 0 because they are not equal
			MOVEQ	 R4,#20     ;this line is not executed because ; the condition EQ is not met
			
			CMP		 R1,#0       ;compare R1 with 0
			ADDNE	 R1,R1,#10   ;this line is executed if Z = 0
			
			ADDNES	 R1,R1,#10
			BX		LR
			
			
    ;without conditional execution	

prog_set_2  
			
			MOV		R0,#0
			MOV		R1,#0
			LDR		R2,=0x9999999
			MOV		R3,#10

L1			ADDS	 R0,R0,R2		;R0 = R0 + R2 and update the flags
			BCC		 NEXT 			;if C = 0, go to next number
			ADD		 R1,R1,#1       ;if C = 1, increment the upper word
NEXT	    SUBS	 R3,R3,#1 		;R3 = R3 - 1 and update the flags
			BNE      L1 				;next round if z = 0
			
			BX		LR
			
			
			; with conditional execution
prog_set_3  
			
			MOV		R0,#0
			MOV		R1,#0
			LDR		R2,=0x9999999
			MOV		R3,#10

L2			ADDS	R0,R0,R2		;;R0 = R0 + R2 and update the flags
			ADDCS   R1,R1,#1 ;if C set (C = 1),increment the upper word
	        SUBS R3,R3,#1 ;R3 = R3 - 1 and update the flags
			BNE 	L2 ;next round if z = 0
			
			BX		LR
			
			
			;find max number using conditional executions
prog_set_4
			MOV		R0,#5  ;count
			MOV		R1,#0  ;max
			LDR		R2,=MyData  ;pointer
Again		LDR		R3,[R2]		;next
			
			CMP		R1,R3  ;c=1,Z=0
			MOVLO	R1,R3
			ADD		R2,R2,#4
			SUBS	R0,R0,#1
			BNE		Again
			BX		LR
			
			
			;playing with signed number
prog_set_5
			LDR		 R0,=SIGN_DAT
			MOV		 R3,#9
			MOV		 R2,#0
LOOP		LDRSB	 R1, [R0]
			ADD		 R2,R2,R1
			ADD		 R0,R0,#1
			SUBS	 R3,R3,#1
			BNE		 LOOP
			LDR		 R0,=SUM
			STR		 R2,[R0]
			BX		LR
			
			;use TST instructions
prog_set_6	

			MOV		 R0,#100
			LDR		 R1,=myPort
OVER		LDRB	 R2,[R1]
			TEQ		 R2,R0
			BNE		 OVER
			MOV		 R0,#100
			MOV		 R0,#100
			BX		 LR
			
			
			

	;Assuming R5 has a positive value, 
	;write a program that finds its negative match in an array of data (OUR_DATA).
prog_set_7

			MOV		R5,#13
			LDR		R1,=OUR_data+1
			MOV		R3,#9
			
begins		LDRSB	R0,[R1]
			CMP		R0,R5 
			BEQ		Found  ;if z=1
			
			ADD		R1,R1,#1
			SUBS	R3,R3,#1
			BNE		begins
			
Notfound     B		Notfound
Found		B		Found
			
			
			
			AREA myData,DATA,READONLY
MyData		DCD		0x55,0x65,0x25,0x96,0x26
SIGN_DAT 	DCB		 +13,-10,+19,+14,-18,-9,+12,-19,+16
SUM			DCD		0
myPort		DCD		100
OUR_data	DCB		+13,-10,-12,+14,-18,-9,+13,-19,+16
			
			ALIGN
			END
					
					
				