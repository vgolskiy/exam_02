#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

static void	*ft_calloc(int len, int size)
{
	char	*str;
	void	*res;
	int		i;

	if (!(res = malloc(len * size)))
		return (00);
	str = (char *)res;
	i = -1;
	while (++i < (len * size))
		str[i] = '\0';
	return (res);
}

static char	*ft_strdup(char *str)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(str);
	if (!(res = ft_calloc(len + 1, sizeof(char))))
		return (00);
	i = -1;
	if (str)
		while (++i < len)
			res[i] = str[i];
	return (res);
}

static void	ft_free(char *left)
{
	if (left)
	{
		free(left);
		left = 00;
	}
}

static char	*add_char(char **s, char ch)
{
	int		i;
	int		j;
	char	*res;

	if (!(res = ft_calloc(ft_strlen(*s) + 2, sizeof(char))))
		return (00);
	i = 0;
	j = -1;
	while ((*s) && ((*s)[++j]))
		res[i++] = (*s)[j];
	ft_free(*s);
	res[i] = ch == '\n' ? '\0' : ch;
	return (res);
}

static int	ft_error(char *left)
{
	ft_free(left);
	return (-1);
}

int	get_next_line(char **line)
{
	int		readed_bytes;
	char	*left;
	char	buf[1];

	left = 00;
	while ((readed_bytes = read(0, buf, 1)) > 0)
	{
		if (!(left = add_char(&left, buf[0])))
			return (ft_error(left));
		if (buf[0] == '\n')
		{
			*line = left;
			return (1);
		}
	}
	if (readed_bytes < 0)
		return (ft_error(left));
	*line = left;
	if (!*line)
		if (!(*line = ft_strdup("")))
			return (ft_error(left));
	return (0);
}
