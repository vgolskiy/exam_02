#include <stdio.h>
#include "get_next_line.h"

int	main()
{
	int		more;
	char	*line;

	line = 00;
	while ((more = get_next_line(&line) > 0))
	{
		printf("%s\n", line);
		free(line);
		line = 00;
	}
	printf("%s", line);
	free(line);
	line = 00;	
	return (0);
}
