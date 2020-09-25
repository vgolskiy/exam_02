#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef	struct	s_format
{
	int			len;
	int			pos;
	int			prec;
	int			prec_mark;
	int			skip_prec;
	char		arg_type;
	char		*subs;
	char		*type;
}				t_format;

void	init_format(t_format *format)
{
	format->len = 0;
	format->pos = 0;
	format->prec = 0;
	format->prec_mark = 0;
	format->skip_prec = 0;
	format->arg_type = '\0';
	format->subs = 00;
	format->type = "sdx";
}

int		ft_isalpha(char ch)
{
	if (((ch >= 'a') && (ch <= 'z')) ||
	((ch >= 'A') && (ch <= 'Z')))
		return (1);
	return (0);
}

int		ft_isdigit(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return (1);
	return (0);
}

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

char	*ft_strchr(char *s, char ch)
{
	int	i;

	i = 0;
	if (s)
		while (s[i])
		{
			if (s[i] == ch)
				return (s + i);
			i++;
		}
	return (00);
}

void	*ft_calloc(int len,  int size)
{
	int		i;
	char	*res;
	char	*s;

	if (!(res = malloc(len * size)))
		return (00);
	s = (char *)res;
	i = -1;
	while (++i < (len * size))
		s[i] = '\0';
	return (res);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(s);
	if (!(res = (char *)ft_calloc(len, sizeof(char))))
		return (00);
	i = -1;
	if (s)
		while (++i < len)
			res[i] = s[i];
	return (res);
}

char	*ft_substr(const char *s, int start, int len)
{
	char	*res;
	int		i;

	if (!s)
		return (00);
	if (start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	if (!(res = (char *)ft_calloc(len + 1, sizeof(char))))
		return (00);
	i = -1;
	while (++i < len)
		res[i] = s[start + i];
	return (res);
}

int		ft_putchar(int c, int len)
{
	int i;

	i = len;
	while (i)
		i -= write(1, &c, 1);
	return (len);
}

int		ft_putstr(const char *str, int precision)
{
	int len;

	len = 0;
	while ((len < precision) && (*str != '\0'))
		len += write(1, str++, 1);
	return (len);
}

int		digits_qty(uintmax_t num, int base)
{
	int len;

	len = 0;
	while (num)
	{
		num /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(uintmax_t n, int base)
{
	int		len;
	char	bases[] = "0123456789abcdef";
	char	*res;

	if (!n)
		return (ft_strdup("0"));
	len = digits_qty(n, base);
	if (!(res = (char *)ft_calloc((len + 1), sizeof(char))))
		return (00);
	while (n)
	{
		res[--len] = bases[n % base];
		n /= base;
	}
	return (res);
}

void	free_subs(t_format *format)
{
	if (format->subs)
		free(format->subs);
}

int		error(t_format *format)
{
	free_subs(format);
	return (-1);
}

int		print_str_prec(t_format *format, char *tmp, int len)
{
	int		res;
	int		gap;

	len = format->prec < len ? format->prec : len;
	gap = 0;
	if (len < format->len)
	{
		format->prec = format->prec > format->len ? format->len : format->prec;
		gap = format->prec > len ? format->prec - len : 0;
	}
	gap += format->len > gap + len ? format->len - gap - len : 0;
	res = ft_putchar(' ', gap);
	res += ft_putstr(tmp, len);
	return (res);
}

int		print_str(t_format *format, va_list args)
{
	char	*tmp;
	int		len;
	int		gap;
	int		res;

	tmp = va_arg(args, char *);
	tmp = !tmp ? "(null)" : tmp;
	len = ft_strlen(tmp);
	if (format->prec_mark)
		return (print_str_prec(format, tmp, len));
	gap = format->len > len ? format->len - len : 0;
	res = ft_putchar(' ', gap);
	res += ft_putstr(tmp, len);
	return (res);
}

int		print_int_prec(t_format *format, char *tmp, int len, int neg)
{
	int	gap;
	int	add;
	int res;

	if (!format->prec)
	{
		free(tmp);
		return (ft_putchar(' ', format->len));
	}
	add = format->prec > len ? format->prec - len : 0;
	gap = format->len > len + neg ? format->len - len - neg : 0;
	if (format->prec > len)
		gap = format->len > format->prec + neg ? format->len - format->prec - neg : 0;
	res = ft_putchar(' ', gap);
	res += neg ? write(1, "-", 1) : 0;
	res += ft_putchar('0', add);
	res += ft_putstr(tmp, len);
	free(tmp);
	return (res);	
}

int		print_int(t_format *format, va_list args)
{
	intmax_t	num;
	char		*tmp;
	int			len;
	int			gap;
	int			res;

	num = (intmax_t)va_arg(args, long int);
	if (!(tmp = ft_itoa_base((num < 0 ? -num : num), 10)))
		return (-1);
	len = ft_strlen(tmp);
	if (format->prec_mark)
		return (print_int_prec(format, tmp, len, num < 0));
	res = num < 0;
	gap = len + res < format->len ? format->len - len - res : 0;
	res += ft_putchar(' ', gap);
	(num < 0) ? write(1, "-", 1) : 0;
	res += ft_putstr(tmp, len);
	free(tmp);
	return (res);
}

int		print_uxx_prec(t_format *format, char *tmp, int len)
{
	int	add;
	int	gap;
	int	res;

	if (!format->prec)
	{
		free(tmp);
		return (ft_putchar(' ', format->len));
	}
	add = format->prec > len ? format->prec - len : 0;
	gap = format->len > len ? format->len - len : 0;
	if (format->prec > len)
		gap = format->len > format->prec ? format->len - format->prec : 0;
	res = ft_putchar(' ', gap);
	res += ft_putchar('0', add);
	res += ft_putstr(tmp, len);
	free(tmp);
	return (res);
}

int		print_uxx(t_format *format, va_list args)
{
	uintmax_t	num;
	char		*tmp;
	int			len;
	int			gap;
	int			res;

	num = (uintmax_t)va_arg(args, unsigned int);
	if (!(tmp = ft_itoa_base(num, 16)))
		return (-1);
	len = ft_strlen(tmp);
	if (format->prec_mark)
		return (print_uxx_prec(format, tmp, len));
	gap = len < format->len ? format->len - len : 0;
	res = ft_putchar(' ', gap);
	res += ft_putstr(tmp, len);
	free(tmp);
	return (res);
}

int		map_funcs(t_format *format, va_list args)
{
	if (format->arg_type == 's')
		return (print_str(format, args));
	if (format->arg_type == 'd')
		return (print_int(format, args));
	if (format->arg_type == 'x')
		return (print_uxx(format, args));
	return (-1);
}

void	parse_flag(t_format *format)
{
	char *tmp;

	tmp = format->subs;
	while ((*tmp) && (ft_isdigit(*tmp)))
		format->len = format->len * 10 + *(tmp++) - 48;
	if (*tmp == '.')
		format->prec_mark = *tmp;
	if (format->prec_mark)
		while ((*tmp) && (ft_isdigit(*tmp)))
			format->prec = format->prec * 10 + *(tmp++) - 48;		
}

int		parse_format(const char *s, t_format *format)
{
	int		delta;
	char	*tmp;
	char	*subs;

	init_format(format);
	tmp = (char *)s;
	while ((*tmp) && (*tmp != '%') && (!ft_isalpha(*tmp)))
		tmp++;
	delta = tmp - s;
	if (!(tmp = ft_strchr(format->type, *tmp)))
		return (-1);
	format->arg_type = *tmp;
	if (!(subs = ft_substr(s, 0, delta)))
		return (-1);
	free_subs(format);
	format->subs = subs;
	format->pos = ++delta;
	parse_flag(format);
	return (1);
}

int		printf_main(const char *s, va_list args)
{
	t_format	format;
	int			len;
	int			delta;

	len = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (parse_format(++s, &format) == -1)
				return (error(&format));
			if ((delta = map_funcs(&format, args)) < 0)
				return (error(&format));
			len += delta;
			s += format.pos;
		}
		else
			len += write(1, s++, 1);
	}
	return (len);
}

int		ft_printf(const char *s, ...)
{
	va_list		args;
	int			len;

	if ((!s) || (!*s))
		return (0);
	va_start(args, s);
	len = printf_main(s, args);
	va_end(args);
	return (len);
}
