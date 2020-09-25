#include <stdarg.h>
#include <unistd.h>

typedef struct	s_type
{
	int		i;
	int		len;
	int		width;
	int		prec_mark;
	int		prec;
	int		neg;
	int		zeros;
	int		res;
	va_list	args;
}				t_type;

void	init_struct(t_type *f)
{
	f->i = 0;
	f->res = 0;
}

void	clear_struct(t_type *f)
{
	f->len = 0;
	f->neg = 0;
	f->prec = 0;
	f->prec_mark = 0;
	f->width = 0;
	f->zeros = 0;
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

int		ft_putchar(char ch, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		write(1, &ch, 1);
	return (len);
}

int		ft_putstr(char *s, int len)
{
	int	i;

	i = -1;
	if (s)
		while ((++i < len) && (s[i]))
			write(1, &s[i], 1);
	return (len);
}

int		ft_isdigit(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return (1);
	return (0);
}

int		long_len_base(long n, int base)
{
	int	i;

	i = 1;
	while (n >= base)
	{
		n /= base;
		i++;
	}
	return (i);
}

void	put_num_base(long n, int base, char *bases)
{
	if (n >= base)
	{
		put_num_base(n / base, base, bases);
		put_num_base(n % base, base, bases);
	}
	else
		ft_putchar(bases[n], 1);
}

void	print_until_perc(const char *s, t_type *f)
{
	while ((s[f->i]) && (s[f->i] != '%'))
		f->res += ft_putchar(s[f->i++], 1);
}

void	parse_flags(const char *s, t_type *f)
{
	f->i++;
	while ((s[f->i]) && (ft_isdigit(s[f->i])))
		f->width = f->width * 10 + s[f->i++] - 48;
	if (s[f->i] == '.')
	{
		f->prec_mark = f->i++;
		while ((s[f->i]) && (ft_isdigit(s[f->i])))
			f->prec = f->prec * 10 + s[f->i++] - 48;
	}	
}

void	print_s(t_type *f)
{
	char	*tmp;

	f->i++;
	tmp = va_arg(f->args, char *);
	if (!tmp)
		tmp = "(null)";
	f->len = ft_strlen(tmp);
	if ((f->prec_mark) && (f->prec < f->len))
		f->len = f->prec;
	f->res += ft_putchar(' ', f->width - f->len);
	f->res += ft_putstr(tmp, f->len);
}

void	print_d(t_type *f)
{
	long	n;

	f->i++;
	n = va_arg(f->args, int);
	if (n < 0)
	{
		f->neg = 1;
		n *= -1;
	}
	f->len = long_len_base(n, 10);
	if ((!n) && (f->prec_mark))
		f->len = 0;
	if ((f->prec_mark) && (f->prec > f->len))
		f->zeros = f->prec - f->len;
	f->res += ft_putchar(' ', f->width - (f->zeros + f->len));
	if (f->neg)
		f->res += ft_putchar('-', 1);
	f->res += ft_putchar('0', f->zeros);
	if ((!n) && (f->prec_mark))
		return ;
	put_num_base(n, 10, "0123456789");
	f->res += f->len;
}

void	print_x(t_type *f)
{
	unsigned int	n;

	f->i++;
	n = va_arg(f->args, unsigned int);
	f->len = long_len_base(n , 16);
	if ((!n) && (f->prec_mark))
		f->len = 0;
	if ((f->prec_mark) && (f->prec > f->len))
		f->zeros = f->prec - f->len;
	f->res += ft_putchar(' ', f->width - (f->zeros + f->len));
	f->res += ft_putchar('0', f->zeros);
	if ((!n) && (f->prec_mark))
		return ;
	put_num_base(n, 16, "0123456789abcdef");
	f->res += f->len;
}

int		ft_printf(const char *s, ...)
{
	t_type f;

	if ((!s) || (!*s))
		return (0);
	init_struct(&f);
	va_start(f.args, s);
	while (s[f.i])
	{
		clear_struct(&f);
		print_until_perc(s, &f);
		if (s[f.i])
		{
			parse_flags(s, &f);
			if (s[f.i] == 's')
				print_s(&f);
			else if (s[f.i] == 'd')
				print_d(&f);
			else if (s[f.i] == 'x')
				print_x(&f);
		}
	}
	va_end(f.args);
	return (f.res);
}
