#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main()
{
	printf("%+d\n", -120); 			//flag "+" => force print +/- sign, also for positive numbers.
	printf("% d\n", 120);  			//flag " " => space is inserted instead of sign.
	printf("%-8d\n", -120); 		//flag "-8" => print atleast 8 characters (extras are blank)". minus for left justify.
	printf("%08d\n", -120); 		//flag "08" => print atleast 8 characters (extras are zeroes)"
	printf("%0*d\n", 8,-120); 		//flag "0*d" => width gives as variadic argument (preceeding). Zeros filled.
	printf("%0.5d\n",-120); 		//flag "0.5d" => .5 is precision. Zeros filled.
	printf("%0.5f\n",-120.5); 		//flag "0.5f" => .5 is precision after the decimal point!. Zeros filled.
	printf("%0.*f\n",20,-120.5); 	//flag "0.*f" => .* is precision after the decimal point!. Zeros filled.
	printf("%%"); 	
	return (0);
}
