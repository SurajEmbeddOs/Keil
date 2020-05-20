
; p= q+r+s
;q=2,r=10,s=12

Q		EQU		2
R		EQU		10
S		EQU		12	
	
				AREA muCode,CODE,READONLY
				ENTRY
				EXPORT		__main

__main
				MOV		R0,#Q
				MOV		R1,#R
				MOV		R2,#S
				
				ADD		R3,R1,R0
				ADD		R3,R3,R2
				
Stop			B			Stop
				
				END
				
				