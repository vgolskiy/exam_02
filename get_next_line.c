/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:17:52 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/23 19:20:22 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*res;

	if ((!str1) && (!str2))
		return (00);
	else if ((!str1) && (str2))
		return (ft_strdup(str2));
	else if ((str1) && (!str2))
		return (ft_strdup(str1));
	if (!(res = ft_calloc(ft_strlen(str1)
		+ ft_strlen(str2) + 1, sizeof(char))))
		return (00);
	i = 0;
	j = -1;
	while (str1[++j])
		res[i++] = str1[j];
	j = -1;
	while (str2[++j])
		res[i++] = str2[j];
	return (res);
}

static int	ft_error(char **left, char **line)
{
	if ((left) && (*left))
		{
			free(*left);
			left = 00;
		}
	if ((line) && (*line))
		{
			free(*line);
			line = 00;
		}
	return (-1);
}

int			get_next_line_buf(char **left, char **line)
{
	char	*tmp;

	tmp = ft_strchr(*left, 10);
	*tmp++ = '\0';
	*line = *left;
	if (!(*left = ft_strdup(tmp)))
		return (ft_error(left, line));
	return (1);
}

int		get_next_line_tail(char **left, char **line)
{
	if (*left)
	{
		if (ft_strchr(*left, 10))
			return (get_next_line_buf(left, line));
		*line = *left;
		*left = 00;
		return (0);
	}
	if (!(*line = ft_strdup("")))
		return (ft_error(left, line));
	return (0);
}

int	get_next_line(char **line)
{
	int			readed_bytes;
	static char	*left;
	char		buf[101];
	char		*tmp;

	while ((readed_bytes = read(0, buf, 100)) > 0)
	{
		buf[readed_bytes] = '\0';
		if (!(tmp = ft_strjoin(left, buf)))
			return (ft_error(&left, line));
		if (left)
			free(left);
		left = tmp;
		if (ft_strchr(left, 10))
			return (get_next_line_buf(&left, line));
	}
	if (readed_bytes < 0)
		return (ft_error(&left, line));
	return (get_next_line_tail(&left, line));
}
