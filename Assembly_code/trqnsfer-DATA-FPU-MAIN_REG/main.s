

				AREA fpu,CODE,READONLY
				ENTRY
				EXPORT		__main
					
__main
				LDR		r0,= 0xE000ED88
				LDR		r1,[r0]
				orr		r1,r1,#(0xf<<20)
				STR		R1,[R0]
				
				LDR		R3,=0x3F800000
				VMOV.F	S3,R3
				
				VLDR.F	S4,=6.0222146e23
				VMOV.F	R4,S4

stop			B		stop
				END