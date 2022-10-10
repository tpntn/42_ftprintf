#include <stdio.h>

int	main()
{
	int 		i = 2;
	int			*ptr;
	ptr = &i;
	printf("address of i with &i: %p\n", &i);
	
	printf("value of p after casting: 0x%10lx\n", (unsigned long)&i);

	//so it seems that the %p == 0x%10lx

	return (0);
}
