
int fun1()
{
	int a=5;
	int b=50;
}

int fun2()
{
	volatile int m=5;
	volatile int n=50;
	fun1();
}

int fun3()
{
	volatile int x=5;
	volatile int y=50;
		fun2();
}

int main()
{
	volatile int a=5;
	volatile int b=50;
	fun3();
	
	while(1);
	
	
}


