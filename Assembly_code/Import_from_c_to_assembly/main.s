


				AREA |.text|,CODE,READONLY
				IMPORT	adder
				IMPORT	num
				EXPORT		__main
__main
				LDR		R1,=num
				MOV		R0,#100
				STR		R0,[r1]
				BL		adder
				
				END
					
					
					