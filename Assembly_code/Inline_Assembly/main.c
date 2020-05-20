

__inline int getsum(int a,int b)
{
	int sum=0;
	__asm{
		ADD sum,a,b
	}
	return sum;
}
int c;
int main()
{
	c=getsum(5,6);
	while(1)
	{
		
	}
	
}



