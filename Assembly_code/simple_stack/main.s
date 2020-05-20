


			AREA myCode,CODE,READONLY
			ENTRY
			EXPORT		__main

__main
			LDR		R2,=0xBABAFACE
			LDR		R3,=0xDEADFACE
			PUSH	{R2}
			PUSH	{R3}
			pop		{R5}
			POP		{R6}

Stop		B		Stop
			ALIGN
			END