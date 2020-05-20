

			AREA swap,CODE,READONLY
			ENTRY
			EXPORT		__main
				
__main
			LDR		R0,=0xBABAFACE
			LDR		R1,=0XDADAFACE
			
			EOR		R0,R0,R1
			EOR		R1,R0,R1
			EOR		R0,R0,R1
			
LOOP   		B		LOOP
			ALIGN
			END
