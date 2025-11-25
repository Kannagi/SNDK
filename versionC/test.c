
const char data1[] = { 0,1,2,3,4};
const short data2[] = { 0,1,2,3,4};
const long data3[] = { 0,1,2,3,4};
void SNDK_print(char *text,unsigned char a,unsigned char b);
unsigned char test(unsigned char a,unsigned char b)
{
	return a+b;
}

unsigned short test2(unsigned short a,unsigned short b)
{
	return a+b;
}


extern 	 unsigned char array8[32];
extern 	  unsigned short array16[32];

int main()
{

	for(int i = 0; i < 32 ;i++)
	{
		array8[i] = i + 2;
		array16[i] = i + 2;
	}
	SNDK_print("test",12,13);
	SNDK_print("test2",12,13);
	SNDK_print("test3",12,13);
	SNDK_print("test4",12,13);
	return 0;
}
