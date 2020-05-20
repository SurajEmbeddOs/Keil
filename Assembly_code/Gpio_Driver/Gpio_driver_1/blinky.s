
RCC_BASE		EQU			0x40023800
RCC_AHB1ENR		EQU			0x40023830	;RCC_BASE+0x30
GPIOA_BASE		EQU			0x40020000
GPIOA_MODE		EQU			GPIOA_BASE
GPIOA_ODR		EQU			0x40020014	;GPIOA_BASE+14


GPIOAEN			EQU			1<<0

MODER5_OUT		EQU			1<<10

LEDON			EQU			1<<5
LED0FF			EQU			0<<5

DELAY			EQU			0x000F

ONESEC			EQU			2666676
HSEC			EQU			266667
FSEC			EQU			106667
	
				AREA	|.text|,CODE,READONLY,ALIGN=2
				THUMB
				EXPORT		__main

__main
				BL		GPIOA_Init


GPIOA_Init
				LDR		R0,=RCC_AHB1ENR ;R0 point to pheripheral clock
				LDR 	R1,[R0]   		;Load content of R0 to R1
				ORR		R1,#GPIOAEN    ;
				STR		R1,[R0]
				
				
				LDR		R0,=GPIOA_MODE  ;R0 point to pheripheral clock
				LDR	    R1,[R0]   		;Load content of R0 to R1
				ORR		R1,#MODER5_OUT    ;
				STR		R1,[R0]
				
				MOV		R1,#0
				LDR		R2,=GPIOA_ODR
				

Blink
				MOVW	R1,#LEDON
				STR		R1,[R2]
				LDR		R3,=ONESEC
				BL		Delay
				
				
				MOVW	R1,#LED0FF
				STR		R1,[R2]
				LDR		R3,=ONESEC
				BL		Delay
				
				B		Blink

Delay
				SUBS	R3,R3,#1
				BNE		Delay
				BX		LR
				

				ALIGN	
				END
					
				

	
				
				
				

