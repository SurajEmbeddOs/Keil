

;P=Q+R+S
				AREA eg4,CODE,READONLY
				ENTRY
				EXPORT		__main

__main
				ADR 	R0,P
				LDR		R1,[R0,#4]
				LDR		R2,[R0,#8]
				LDR		R3,[R0,#12]
				
				ADD		R4,R1,R2
				ADD		R4,R4,R3
				

stop			B		stop

			
						
				AREA eg4,DATA,READONLY
P				SPACE		4
				DCD			2
				DCD			10
				DCD			12
				
				ALIGN
				END


