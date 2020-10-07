#include <unistd.h>

int	ft_upper(char ch)
{
	if ((ch >= 'A') && (ch <= 'Z'))
		return (1);
	return (0);
}

int	ft_lower(char ch)
{
	if ((ch >= 'a') && (ch <= 'z'))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	rep;

	if (argc == 2)
	{
		i = -1;
		while (argv[1][++i])
		{
			rep = 1;
			if (ft_upper(argv[1][i]))
				rep += argv[1][i] - 'A';
			else if (ft_lower(argv[1][i]))
				rep += argv[1][i] - 'a';
			while (--rep >= 0)
				write(1, &argv[1][i], 1);
		}
	}
	write(1, "\n", 1);
	return (0);
}
