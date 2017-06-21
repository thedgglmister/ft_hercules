#include "libft.h"
#include <stdio.h>

int main(void)
{
	char *buf;

	while(ft_gnl(0, &buf))
		printf("%s\n", buf);

	printf("done\n");

	return(0);
}
