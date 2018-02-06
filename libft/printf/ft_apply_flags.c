/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:59:10 by skushnir          #+#    #+#             */
/*   Updated: 2017/12/29 12:31:34 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_nonconv(char *str)
{
	if (g_f.flags[4])
		while (--g_f.w > 0)
			ft_putchar('0');
	if (!g_f.flags[0])
		while (--g_f.w > 0)
			ft_putchar(' ');
	ft_putchar(*str);
	if (g_f.flags[0])
		while (--g_f.w > 0)
			ft_putchar(' ');
	return (1);
}

static void	ft_output(t_conver *c, t_basic *types, int lol, int *arg)
{
	if (ft_strpcmp(c->conv, "SscCeEfF") && g_f.flags[4])
		while (g_f.w-- > g_f.p)
			ft_putchar('0');
	if (!g_f.flags[0])
		while (g_f.w-- > g_f.p)
			ft_putchar(' ');
	if (g_f.flags[1] && ft_strpcmp(c->conv, "dDieEfF")
		&& *arg >= 0)
		ft_putchar('+');
	if ((g_f.flags[3] && (c->size <= 7 || c->size >= 9)
		&& *arg <= 0) || c->size == 8)
		ft_putstr(c->prefix);
	!lol ? ft_wr_func(c, *types, c->wrfunc) : 0;
	if (g_f.flags[0])
		while (g_f.w-- > g_f.p)
			ft_putchar(' ');
	return ;
}

static void	ft_apply_nbr2(t_conver *c, t_basic *types, int *arg)
{
	g_f.w > g_f.p && ft_strpcmp(c->conv, "eEfF") ?
	g_f.w -= (int)ft_len_func(c, *types, c->lenf) - g_f.p : 0;
	if ((*arg != 1 && g_f.flags[3]) || c->size == 8)
	{
		g_f.w > (int)ft_strlen(c->prefix) ? g_f.w -= ft_strlen(c->prefix) : 0;
		if (*arg != 1 && ft_strpcmp(c->conv, "oO") && g_f.p > 1)
			g_f.p -= 1;
		g_f.flags[4] && ft_strpcmp(c->conv, "p") ? g_f.p = g_f.w : 0;
	}
	if (*arg == -1 && ft_strpcmp(c->conv, "dDi") &&
		g_f.p >= (int)ft_len_func(c, *types, c->lenf))
		g_f.p++;
	if ((!g_f.flags[8] && !ft_strpcmp(c->conv, "SscC")) && g_f.flags[4] &&
		!g_f.flags[0] && (c->size <= 7 || c->size >= 12 || c->size == 9))
		g_f.p = g_f.w;
	if (g_f.p < (int)ft_len_func(c, *types, c->lenf) && c->size < 12)
		g_f.p = ft_len_func(c, *types, c->lenf);
	ft_output(c, types, 0, arg);
	return ;
}

static void	ft_apply_nbr(t_conver *c, t_basic *types, int *arg)
{
	g_f.p < 0 ? g_f.p = g_f.w : 0;
	if (g_f.flags[2] && ft_strpcmp(c->conv, "dDi") &&
		!g_f.flags[1] && *arg >= 0)
	{
		ft_putchar(' ');
		g_f.w--;
	}
	ft_strpcmp(c->conv, "cC") ? g_f.p = 0 : 0;
	((ft_strpcmp(c->conv, "cC") && *arg == 1)) ? g_f.p = 1 : 0;
	if (((!ft_strpcmp(c->conv, "oO"))) || !g_f.flags[3])
		if (*arg == 1 && g_f.flags[8] && !g_f.p)
		{
			ft_output(c, types, 1, arg);
			return ;
		}
	ft_strpcmp(c->conv, "dDieEfF") && g_f.flags[1] && *arg != -1 ? g_f.w-- : 0;
	if (!g_f.flags[8])
	{
		c->size >= 12 ? g_f.p = 6 : 0;
		c->size == 8 ? g_f.p = ft_len_func(c, *types, c->lenf) : 0;
	}
	ft_apply_nbr2(c, types, arg);
	return ;
}

void		ft_apply_flags(va_list *ap)
{
	int			arg;
	size_t		i;
	t_basic		types;
	t_conver	c;

	i = 0;
	while (ft_strcmp(g_c[i].conv, g_f.conversion))
		i++;
	c = g_c[i];
	set_types(&c, &types, ap);
	arg = arg_zero(&types, &c);
	if (ft_strpcmp(c.conv, "sS"))
	{
		i = ft_len_func(&c, types, c.lenf);
		if (g_f.flags[8] && !g_f.p)
			i = 0;
		(g_f.p <= 0 || !i || g_f.p > (int)i) ? g_f.p = i : 0;
		if (ft_strchr(c.conv, 'S') &&
			g_f.p > (int)(i = ft_strunlen(*(void **)&types, g_f.p)))
			g_f.p = i;
		arg == 1 && !g_f.p ? types.p = "\0" : 0;
		ft_output(&c, &types, 0, &arg);
	}
	else
		ft_apply_nbr(&c, &types, &arg);
}
