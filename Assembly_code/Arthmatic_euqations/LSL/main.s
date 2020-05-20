

			AREA myCode,CODE,READONLY
			ENTRY
			EXPORT		__main

__main

			MOV		R0,#0x11
			LSL		R1,R0,#1
			LSL		R2,R1,#1
			
			
stop		B		stop
			
			END
			