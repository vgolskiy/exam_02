/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:17:52 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/29 12:12:29 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line3.h"

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

static char	*ft_strchr(char *str, int ch)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
			if (str[i] == ch)
				return (str + i);
	}
	return (00);
}

static char	*add_char(char *s, char ch)
{
	int		i;
	char	*res;

	if (!(res = ft_calloc(ft_strlen(s) + 2, sizeof(char))))
		return (00);
	i = -1;
	while ((s) && (s[++i]))
		res[i] = s[i];
	res[i] = (ch == '\n') ? '\0' : ch;
	return (res);
}

static int	ft_error(char **left)
{
	if ((left) && (*left))
		{
			free(*left);
			left = 00;
		}
	return (-1);
}

int	get_next_line(char **line)
{
	int			readed_bytes;
	static char	*left;
	char		ch[1];
	char		*tmp;

	while ((readed_bytes = read(0, ch, 1)) > 0)
	{
		if (!(tmp = add_char(left, ch)))
			return (ft_error(&left));
		if (left)
			free(left);
		left = tmp;
		if (ch == '\n')
		{
			*line = left;
			return (1);
		}
	}
	if (readed_bytes < 0)
		return (ft_error(&left));
	*line = left;
	if (!(*line = ft_strdup("")))
		return (ft_error(left));
	return (0);
}
