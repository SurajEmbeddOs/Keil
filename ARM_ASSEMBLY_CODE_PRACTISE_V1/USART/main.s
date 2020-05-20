
;USART2  PA2=TX,PA1=RX
	      AREA mydata,DATA,READONLY
print			DCB		'h','e','l','l','o',' ','s','u','r','a','j','\n','\r'



RCC_BASE		 			EQU			0x40023800
GPIOA_BASE					EQU			0x40020000
USART2_BASE					EQU			0x40004400
	
RCC_AHB1EN_OFFSET			EQU			0x30
RCC_APB1EN_OFFSET			EQU			0x40


GPIOA_Port					EQU			(1<<0)  ;
USART_Port					EQU			(1<<17)
TXE_Bit						EQU			(1<<7)
	
USART2_DR					EQU			0x40004404
USART2_SR					EQU			USART2_BASE		



				AREA usart_conf,CODE,READONLY
				ENTRY	
				EXPORT		__main


__main
				BL		Gpio_Init
				BL		Uart_Init
				LDR		R8,=USART2_DR
				
			
				
				
loop			LDR		R5,=print
				MOV		R0,#13
				
Send			LDRB	R4,[R5]				
			
				LDR		R1,=USART2_SR
Again			LDR		R2,[R1]
				TEQ		R2,#TXE_Bit  ;check R2 is same as TXE_Bit if equal go next otherwise wait until same
				BEQ		Again
				
				LDR		R10,=555
				BL		Delay
				
				STRB	R4,[R8]
				ADD		R5,R5,#1
				SUBS	R0,R0,#1
				BNE		Send
				
				LDR		R10,=555
				BL		Delay
				
			    B     loop
				
			
				

							
stop			 B			stop

Delay			
				
L1				SUBS	R10,R10,#1
				BNE		L1
				BX		LR

Gpio_Init		
				LDR		R1,    =RCC_BASE
				ADD		R1,R1,#RCC_AHB1EN_OFFSET  ;RCC_BASE+RCC_AHB1EN_OFFSET ;0x40023830
				LDR		R2,[R1]
				ORR		R2,R2,#GPIOA_Port
				
				STR		R2,[R1]    ;ENABLE CLOCK for GPOIA port
				
				;configure GPIOA pin 2 as USART2 TX
				LDR		R1,    =GPIOA_BASE
				LDR		R2,[R1]
				ORR		R2,R2,#(0x2<<4)
				
				STR		R2,[R1]  ;gpioa pin 2 set alternate function mode
				
				LDR		R1,    =GPIOA_BASE
				ADD		R1,R1,#0x0C
				LDR		R2,[R1]
				ORR		R2,R2,#(0x1<<4)
				
				STR		R2,[R1]  ;gpioa pin 2 set Pull up

				LDR		R1,    =GPIOA_BASE
				ADD		R1,R1,#0x20
				LDR		R2,[R1]
				ORR		R2,R2,#(0x7<<8)
				
				STR		R2,[R1]  ;gpioa pin 2 alternate function low register
				
				BX  LR	
				
Uart_Init
				
				LDR		R1,    =RCC_BASE
				ADD		R1,R1,#RCC_APB1EN_OFFSET  ;RCC_BASE+RCC_AHB1EN_OFFSET ;0x40023830
				LDR		R2,[R1]
				ORR		R2,R2,#USART_Port
				
				STR		R2,[R1]    ;ENABLE CLOCK for USART2 port
				
				;configure GPIOA pin 2 as USART2 TX
				LDR		R1,    =USART2_BASE
				ADD		R1,R1,#0x08  ;baud rate offset
				MOV		R2,#0x8B	;configure baud rate 
				
				STR		R2,[R1]  ;set boud rate at 115200
				
				LDR		R1,    =USART2_BASE
				ADD		R1,R1,#0x0C ;CR1 register offset
				LDR		R2,[R1]
				ORR		R2,R2,#(0x1<<3)   ;Enable USART2 TX
				ORR		R2,R2,#(0x1<<13)  ;Enable USART2 TX
				
				STR		R2,[R1]  ;Enable usart for transmitting mode 
				
				BX  LR	
				
				
				ALIGN
				END
				
				
				

				
