#include <stdio.h>
#include <math.h>
#include "incs/vec3.h"

int main()
{
	int	ret;
	int	tmp;

	ret = 0;
	tmp = 1;
	ret |= tmp;
	printf("%d\n", ret);
}
