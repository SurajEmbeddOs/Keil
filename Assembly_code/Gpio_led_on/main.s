
;0x40023800
GPIOA_RCC_CLOCK_R   EQU		0x40023880
GPIOA_MODE_R		EQU		0x40020000
GPIOA_ODR_R		    EQU		0x40020014
	

					AREA  |.text |,CODE,READONLY,ALIGN=2
					THUMB
					EXPORT __main
						
__main
			BL 	GPIO_Init
			
loop		BL	GPIO_ON
			B	loop

GPIO_Init  
			LDR R1,=GPIOA_RCC_CLOCK_R
			LDR R0,[R1]
			ORR R0,R0,#0x00
			STR R0,[R1]
			
			LDR R1,=GPIOA_MODE_R
			LDR R0,=0x400
			STR R0,[R1]
			
			
			
			BX  LR	
			
			
GPIO_ON
		    LDR R1,=GPIOA_ODR_R
			LDR R0,=0x20
			STR R0,[R1]
			
			BX  LR
			ALIGN
			END
			