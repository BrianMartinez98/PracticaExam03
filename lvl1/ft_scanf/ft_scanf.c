#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int	match_space(FILE *f)
{
	int	c;

	c = fgetc(f);
	while (c != EOF && isspace(c))
		c = fgetc(f);
	if (c != EOF)
		ungetc(c, f);
	return (0);
}

int	match_char(FILE *f, char c)
{
	int	input;

	input = fgetc(f);
	if (input == EOF)
		return (-1);
	if (input == c)
		return (1);
	ungetc(input, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	char	*ptr;
	int		c;

	c = fgetc(f);
	if (c == EOF)
		return (-1);
	ptr = va_arg(ap, char *);
	*ptr = c;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	int		*ptr;
	int		sign;
	int		digits;
	int		result;
	int		c;

	sign = 1;
	digits = 0;
	result = 0;
	c = fgetc(f);
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (c != EOF && isdigit(c))
	{
		result = result * 10 + (c - '0');
		digits++;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	if (digits == 0)
		return (0);
	ptr = va_arg(ap, int *);
	*ptr = result * sign;
	return (1);
}

int	scan_string(FILE *f, va_list ap)
{
	char	*str;
	int		c;
	int		i;

	str = va_arg(ap, char *);
	c = fgetc(f);
	i = 0;
	while (c != EOF && !isspace(c))
	{
		str[i++] = c;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	str[i] = '\0';
	if (i == 0)
		return (0);
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	if (**format == 'c')
		return (scan_char(f, ap));
	if (**format == 'd')
	{
		match_space(f);
		return (scan_int(f, ap));
	}
	if (**format == 's')
	{
		match_space(f);
		return (scan_string(f, ap));
	}
	return (-1);
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	nconv;
	int	ret;

	nconv = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret = match_conv(f, &format, ap);
			if (ret != 1)
				return (nconv ? nconv : ret);
			nconv++;
		}
		else if (isspace(*format))
			match_space(f);
		else if (match_char(f, *format) != 1)
			return (nconv);
		format++;
	}
	if (ferror(f))
		return (EOF);
	return (nconv);
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}
