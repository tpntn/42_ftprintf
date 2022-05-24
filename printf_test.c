#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

union u_double
{
    double  dbl;
    char    data[sizeof(double)];
};

static void dump_double(union u_double d)
{
	int exp;
	long long mant;

	printf("64-bit float: sign: %d, ", (d.data[0] & 0x80) >> 7);
	exp = ((d.data[0] & 0x7F) << 4) | ((d.data[1] & 0xF0) >> 4);
	printf("expt: %4d (unbiassed %5d), ", exp, exp - 1023);
	mant = ((((d.data[1] & 0x0F) << 8) | (d.data[2] & 0xFF)) << 8) | (d.data[3] & 0xFF);
	mant = (mant << 32) | ((((((d.data[4] & 0xFF) << 8) | (d.data[5] & 0xFF)) << 8) | (d.data[6] & 0xFF)) << 8) | (d.data[7] & 0xFF);
	printf("mant: %16lld (0x%013llX)\n", mant, mant);
}

static void raw_double(union u_double d)
{
	int mask = 0xFF;
	printf("%d\n\n", d.data[0] & mask);
	for (int i = 7; i >= 0; i--)
	{
		for (int c = 7; c >= 0; c--)
			printf("%d", (d.data[i] >> c) & 1);
	}
}

union number
{
	double a;
	char b;
};

int	main()
{
	printf("%+d\n", -120); 					//flag "+" => force print +/- sign, also for positive numbers.
	printf("% d\n", 120);  					//flag " " => space is inserted instead of sign.
	printf("%-8d\n", -120);					//flag "-8" => print atleast 8 characters (extras are blank)". minus for left justify.
	printf("%08d\n", -120); 				//flag "08" => print atleast 8 characters (extras are zeroes)"
	printf("%0*d\n", 8,-120); 				//flag "0*d" => width gives as variadic argument (preceeding). Zeros filled.
	printf("%0.5d\n",-120); 				//flag "0.5d" => .5 is precision. Zeros filled.
	printf("%0.5f\n",-120.5); 				//flag "0.5f" => .5 is precision after the decimal point!. Zeros filled.
	printf("%0.*f\n",20,-120.5); 			//flag "0.*f" => .* is precision after the decimal point!. Zeros filled.
	printf("%.10f\n",-120.51233478234);
	printf("%.200f\n",-120.51233478234); 	
	printf("%%\n"); 	

	// union number a = {.a = -120.51233478234};

	// for (int i = 0; i < 64; i++)
	// {
	// 	printf("%d", ((a.b & 1) >> i));
	// }

	union u_double d;
	d.dbl = -0.01171875;
	dump_double(d);
	raw_double(d);

	return (0);
}
