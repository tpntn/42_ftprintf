#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void
myfunc(void *ptr, ...)
{
    va_list va;
    void *p;

    va_start(va, ptr);
	p = ptr;
	while (p != NULL)
	{
		printf("%p\n", p);
		p = va_arg(va, void *);
	}
    va_end(va);
}

int
main() {
    myfunc(main, myfunc, printf, NULL);
    return 0;
}