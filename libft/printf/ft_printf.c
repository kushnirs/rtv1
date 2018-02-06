/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 22:25:16 by sergee            #+#    #+#             */
/*   Updated: 2017/12/29 10:19:46 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_find_conversion(char *str, va_list *ap)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr("hljzL", str[i]))
			g_f.conversion[i] = str[i];
		else if (ft_strchr("dDcCuUxXeEfFgGsSoOipbB", str[i]))
		{
			g_f.conversion[i] = str[i];
			g_f.conversion[i + 1] = 0;
			break ;
		}
		else
			break ;
	}
	if (!ft_strchr("dDcCuUxXeEfFgGsSoOipbB", str[i]))
		return (ft_nonconv(&str[i]));
	ft_apply_flags(ap);
	return (i + 1);
}

static int	ft_width(char *str, va_list *ap)
{
	int i;

	i = 0;
	if (str[i] == '*')
		g_f.w = va_arg(*ap, int);
	else
	{
		g_f.w = 0;
		while (str[i] >= '0' && str[i] <= '9')
			g_f.w = g_f.w * 10 + (str[i++] - 48);
		i--;
	}
	if (g_f.w < 0)
	{
		g_f.w = -g_f.w;
		g_f.flags[0] = 1;
	}
	return (i);
}

static int	ft_precision(char *str, va_list *ap)
{
	int i;

	g_f.flags[8] = 1;
	i = 0;
	if (str[i] == '.' && str[i + 1] == '*')
		g_f.p = va_arg(*ap, int);
	else if (str[i] == '.' && str[i + 1] >= '0' && str[i + 1] <= '9' && ++i)
		while (str[i] >= '0' && str[i] <= '9')
			g_f.p = g_f.p * 10 + (str[i++] - 48);
	return (i);
}

static int	ft_read_flags(char *str, va_list *ap)
{
	int i;

	i = -1;
	while (str[++i])
	{
		str[i] == '-' ? g_f.flags[0] = 1 : 0;
		str[i] == '+' ? g_f.flags[1] = 1 : 0;
		str[i] == ' ' ? g_f.flags[2] = 1 : 0;
		str[i] == '#' ? g_f.flags[3] = 1 : 0;
		str[i] == '0' ? g_f.flags[4] = 1 : 0;
		str[i] == '$' ? g_f.flags[5] = 1 : 0;
		str[i] == '`' ? g_f.flags[6] = 1 : 0;
		str[i] == '\'' ? g_f.flags[7] = 1 : 0;
		str[i] == '.' ? g_f.flags[8] = 1 : 0;
		if ((str[i] == '*' && str[i - 1] != '.') ||
			(str[i] > '0' && str[i] <= '9' && str[i - 1] != '.'))
			i += ft_width(&str[i], ap);
		str[i] == '.' ? i += ft_precision(&str[i], ap) : 0;
		if (!ft_strchr("-+ #0$.*0123456789", str[i]))
			break ;
	}
	g_f.flags[0] ? g_f.flags[4] = 0 : 0;
	str[i] ? i += ft_find_conversion(&str[i], ap) : 0;
	return (i);
}

int			ft_printf(const char *format, ...)
{
	char	*str;
	va_list	ap;

	g_symb = 0;
	str = (char*)format;
	va_start(ap, format);
	while (*str)
	{
		if (*str == '%')
		{
			str += ft_read_flags(str + 1, &ap);
			ft_free();
		}
		else
			ft_putchar(*str);
		str++;
	}
	format ? va_end(ap) : 0;
	return (g_symb);
}
