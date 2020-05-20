

		AREA	DATA
Size	EQU		8
Putpt	SPACE	4
Getpt	SPACE	4
Fifo	SPACE	Size


		EXPORT	Putpt	[DATA,SIZE=4]
		EXPORT	Getpt	[DATA,SIZE=4]
		EXPORT	Fifo	[DATA,SIZE=8]


		EXPORT	Fifo_init	
		EXPORT	Fifo_put	
		EXPORT	Fifo_get
		EXPORT	Fifo_size
			
			AREA |.text| ,CODE,READONLY
			

Fifo_init
			LDR		R0,=Fifo
			LDR		R1,=Putpt
			STR		R0,[R1]

			LDR		R1,=Getpt
			STR		R0,[R1]
			BX		LR

Fifo_put

			LDR		R1,=Putpt
			LDR		R2,[R1]
			ADD		R3,R2,#1
			LDR		R12,=Fifo+Size
			CMP		R3,R12
			BNE		NoWrap
			LDR		R3,=Fifo

NoWrap
			LDR		R12,=Getpt
			LDR		R12,[R12]
			CMP		R3,R12
			BNE		NotFull		;not full
			MOV		R0,#0
			BX		LR

NotFull
			STRB	R0,[R2]	
			STR		R3,[R1]
			MOV		R0,#1
			BX		LR
			
Fifo_get
			PUSH	{R4,R5,LR}
			LDR		R1,=Putpt
			LDR		R1,[R1]
			LDR		R2,=Getpt
			LDR		R3,[R2]
			CMP		R1,R3
			BNE		NotEmpty
			MOV		R0,#0
			B		Done

NotEmpty
			LDRSB	R4,[R3]
			STRB	R4,[R0]
			LDR		R5,Fifo+Size
			CMP		R3,R5
			BNE		NoWrap2
			LDR		R3,=Fifo
			
NoWrap2
			STR		R3,[R2]

Done	
			POP		{R4,R5,PC}
			
Fifo_size
			LDR 	R1,=Putpt
			LDR		R1,[R1]
			LDR		R2,=Getpt
			LDR		R3,[R2]
			SUB		R0,R1,R3
			AND		R0,#(Size-1)
			
			BX		LR
			ALIGN
			END

			
			