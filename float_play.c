#include <libft.h>
#include <stdio.h>

//gcc float_play.c -I Libft/ -L libft -lft

void	ft_printf_float(float f, int prec)
{
	float	stby;
	char	*intgr;
	char	*digits;
	int		i;
	float	multp;
	float	temp;

	if(f < 0)
	{
		ft_putchar('-');
		f *= -1;
	}

	digits = (char *)malloc(sizeof(char) * (prec + 2));
	if (!digits)
		exit(1);
	stby = (int)f;
	intgr = ft_itoa((int)stby);

	ft_putstr(intgr);
	ft_putstr(".");
	f -= stby;

	i = 0;
	multp = 10.0;
	while(i <= prec)
	{
		temp = f * multp;
		printf("%f\n",temp);
		stby = (int)(f);
		digits[i++] = (stby + 48);
		multp *= 10.0;
		f -= stby;
	}
	digits[i] = '\0';
	if (digits[i - 1] >= (5 + 48))
		digits[i-2]++;
	i = 0;
	while (i < prec)
		ft_putchar(digits[i++]);
	
}

int	main()
{
	float 	f = 1.00000011921;
	int		prec = 40;
	float	mult = 1.0;
	float	temp;
	int		digit;
	


	printf("%.40f\n",f);

	printf("sizeof int: %zu\n",sizeof(int));
	printf("=> bytes %d", 4*8);
	
	// ft_printf_float(f,prec);	
	return (0);
}