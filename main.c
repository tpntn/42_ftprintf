// gcc -Wall main.c -I ./Libft -I ./includes -L ./Libft -lft -L./ -lftprintf

#include "libft.h"
#include "ft_printf.h"

void	float_tests()
{
	float f = 12.15;
	ft_printf("%.18f\n",f);
	printf("%.18f\n\n",f);

	ft_printf("% 7.2f\n",f);
	printf("% 7.2f\n\n",f);

	ft_printf("%+7.2f\n",f);
	printf("%+7.2f\n\n",f);

	ft_printf("%0+f\n",f);
	printf("%0+f\n\n",f);

	ft_printf("%f\n",f);
	printf("%f\n",f);

	f = -12.15;
	ft_printf("%07.2f\n",f);
	printf("%07.2f\n\n",f);

	ft_printf("%7.2f\n",f);
	printf("%7.2f\n\n",f);

	ft_printf("%+7.2f\n",f);
	printf("%+7.2f\n\n",f);

	ft_printf("%+.5f\n",f);
	printf("%+.5f\n\n",f);

	ft_printf("% 20.9f\n",f);
	printf("% 20.9f\n",f);

	//THIS WILL CRASH THE ROUNDER, CHECK ROUNDER
	// f = __FLT_MAX__;
	// ft_printf("%f\n",f);
	// printf("%f\n",f);

	f = 12.1;
	ft_printf("%f\n",f);
	printf("%f\n",f);

	f = 12.0;
	ft_printf("%.0f\n",f);
	printf("%.0f\n",f);

	f = 0.0;
	ft_printf("%7.3f\n",f);
	printf("%7.3f\n",f);

	f = 11.12;
	ft_printf("%.3f\n",f);
	printf("%.3f\n",f);

	ft_printf("%-12.3f\n",f);
	printf("%-12.3f\n",f);

	f = -11.12;
	ft_printf("%.3f\n",f);
	printf("%.3f\n",f);

	ft_printf("%-12.3f\n",f);
	printf("%-12.3f\n",f);

	
}

void	int_test()
{
	int a = 0;
	ft_printf("ft:\t%d\n", a);
	printf("lib:\t%d\n\n", a);

	a = INT_MIN;
	ft_printf("ft:\t%d\n", a);
	printf("lib:\t%d\n\n", a);

	a = INT_MAX;
	ft_printf("ft:\t%d\n", a);
	printf("lib:\t%d\n\n", a);

	long b = LONG_MAX;
	ft_printf("ft:\t%ld\n", b);
	printf("lib:\t%ld\n\n", b);

	b = LONG_MIN;
	ft_printf("ft:\t%ld\n", b);
	printf("lib:\t%ld\n\n", b);

	long long c = __LONG_LONG_MAX__;
	ft_printf("%lld\n", c);
	printf("%lld\n\n", c);

	c = LLONG_MIN;
	ft_printf("%lld\n", c);
	printf("%lld\n\n", c);

	unsigned int d = UINT16_MAX;
	ft_printf("%u\n", d);
	printf("%u\n\n", d);

	d = 0;
	ft_printf("ft:\t%u\n", d);
	printf("lib:\t%u\n\n", d);

	int e = 522;
	ft_printf("ft:\t%x\n", e);
	printf("lib:\t%x\n\n", e);

	int f = -522;
	ft_printf("ft:\t%x\n", f);
	printf("lib:\t%x\n\n", f);

	unsigned long long g = LLONG_MAX;
	ft_printf("ft:\t%llx\n", g);
	printf("lib:\t%llx\n\n", g);

}

int main()
{
	// float f = __FLT_MAX__;
	// float f = 100.0;
	// printf("%f\n",f);
	// printf("%#f\n",f);
	// printf("%020f\n",f);

	// float f = 0.1;
	// printf("%.1f\n",f);
	// ft_printf("%.1f\n",f);
	
	// printf("%.2f\n",f);
	// ft_printf("%.2f\n",f);

	// printf("%.3f\n",f);
	// ft_printf("%.3f\n",f);

	// printf("%.4f\n",f);
	// ft_printf("%.4f\n",f);

	// printf("%.5f\n",f);
	// ft_printf("%.5f\n",f);

	// printf("%.6f\n",f);
	// ft_printf("%.6f\n",f);

	// printf("%.7f\n",f);
	// ft_printf("%.7f\n",f);

	// printf("%.8f\n",f);
	// ft_printf("%.8f\n",f);

	// printf("%.9f\n",f);
	// ft_printf("%.9f\n",f);

	// printf("%.10f\n",f);
	// ft_printf("%.10f\n",f);

	// printf("%.11f\n",f);
	// ft_printf("%.11f\n",f);

	// printf("%.25f\n",f);
	// ft_printf("%.25f\n",f);

	// printf("%.35f\n",f);
	// ft_printf("%.35f\n",f);

	// printf("%.45f\n",f);
	// ft_printf("%.45f\n",f);

	// printf("%.46f\n",f);
	// ft_printf("%.46f\n",f);

	// printf("%.101f\n",f);
	// ft_printf("%.101f\n",f);
	
	// int a = 52212123;
	// ft_printf("%d \n",a);


	
	
	

	// char *s = "123";
	// ft_printf("this is string %s inside a string\n", s);
	// printf("this is string %s inside a string\n\n", s);

	// char x = 'c';
	// ft_printf("char in %c string\n", x);
	// printf("char in %c string\n\n", x);

	// ft_printf("address of x: %p\n", &x);
	// printf("address of x: %p\n\n", &x);
	
	// int a = 52212123;
	// ft_printf("%x \n",a);
	// printf("%x \n",a);
	// ft_printf("%p \n", &a);
	// printf("%p \n", &a);
	
	float_tests();
	// int_test();

	// ft_printf("This is %% random\n\n");

	// float f = 12.15;
	// printf("%%07.2f\n");
	// ft_printf("%f\n",f);
	// printf("%f\n\n",f);

	// ft_printf("printf: __FLT_MIN__:\t%.150lf\n",__FLT_MIN__);
	// ft_printf("printf: __DBL_MIN__:\t%Lf\n",__DBL_MIN__);
	// ft_printf("This is amasing %.40f asd\n", __FLT_MIN__);
	// printf("This is amasing %.40f asd\n", __FLT_MIN__);
	// printf("This is \n amasing %- #123.42f asd\n",1.0);
	// ft_printf("g %+42lu");

	
	return (0);
}