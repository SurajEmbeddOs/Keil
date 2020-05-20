


		IMPORT	Fifo_init	
		IMPORT	Fifo_put	
		IMPORT	Fifo_get
		IMPORT	Fifo_size
			
		AREA	DATA
n		SPACE	8
		EXPORT	n
			
			AREA	Mycode,CODE,READONLY
			EXPORT		__main

__main
			BL		Fifo_init
			
			MOV		R0,#10
			BL		Fifo_put
			MOV		R0,#20
			BL		Fifo_put
            MOV		R0,#30
			BL		Fifo_put
			MOV		R0,#40
			BL		Fifo_put
			MOV		R0,#50
			BL		Fifo_put
			MOV		R0,#60
			BL		Fifo_put
			MOV		R0,#70
			BL		Fifo_put
			MOV		R0,#80
			BL		Fifo_put
			
			
Stop		B		Stop
			END