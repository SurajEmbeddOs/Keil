



extern void SystemInit(void);
extern int __main(void);



int main()
{
	
	while(1);
	
}

void Reset_Handler(void)
{
	SystemInit();
	__main();
	
}