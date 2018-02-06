/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 01:03:20 by sergee            #+#    #+#             */
/*   Updated: 2017/12/29 12:26:36 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t g_symb = 0;
t_flags g_f = {{0}, 0, 0, {0}};
t_conver	g_c[] = {
	{"d", ft_nbr, ft_nbrlen, 7, ""},
	{"hd", ft_nbr, ft_nbrlen, 6, ""},
	{"hhd", ft_nbr, ft_nbrlen, 4, ""},
	{"jd", ft_lnbr, ft_lnbrlen, 9, ""},
	{"zd", ft_lnbr, ft_lnbrlen, 10, ""},
	{"ld", ft_lnbr, ft_lnbrlen, 9, ""},
	{"lld", ft_lnbr, ft_lnbrlen, 9, ""},
	{"D", ft_lnbr, ft_lnbrlen, 9, ""},
	{"hD", ft_lnbr, ft_lnbrlen, 9, ""},
	{"hhD", ft_lnbr, ft_lnbrlen, 9, ""},
	{"lD", ft_lnbr, ft_lnbrlen, 9, ""},
	{"llD", ft_lnbr, ft_lnbrlen, 9, ""},
	{"jD", ft_lnbr, ft_lnbrlen, 9, ""},
	{"zD", ft_lnbr, ft_lnbrlen, 10, ""},
	{"i", ft_nbr, ft_nbrlen, 7, ""},
	{"hi", ft_nbr, ft_nbrlen, 6, ""},
	{"hhi", ft_nbr, ft_nbrlen, 4, ""},
	{"zi", ft_lnbr, ft_lnbrlen, 10, ""},
	{"li", ft_lnbr, ft_lnbrlen, 9, ""},
	{"lli", ft_lnbr, ft_lnbrlen, 9, ""},
	{"ji", ft_lnbr, ft_lnbrlen, 9, ""},
	{"o", ft_o_nbr, ft_o_nbrlen, 7, "0"},
	{"ho", ft_o_nbr, ft_o_nbrlen, 5, "0"},
	{"hho", ft_o_nbr, ft_o_nbrlen, 3, "0"},
	{"zo", ft_o_lnbr, ft_o_lnbrlen, 10, "0"},
	{"jo", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"lo", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"llo", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"O", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"zO", ft_o_lnbr, ft_o_lnbrlen, 10, "0"},
	{"hO", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"hhO", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"jO", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"lO", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"llO", ft_o_lnbr, ft_o_lnbrlen, 9, "0"},
	{"s", ft_putnstr, ft_strnlen, 8, ""},
	{"S", ft_putunstr, ft_strunlen, 8, ""},
	{"hS", ft_putunstr, ft_strunlen, 8, ""},
	{"hhS", ft_putunstr, ft_strunlen, 8, ""},
	{"ls", ft_putunstr, ft_strunlen, 8, ""},
	{"x", ft_x_nbr, ft_x_nbrlen, 7, "0x"},
	{"zx", ft_x_lnbr, ft_x_lnbrlen, 10, "0x"},
	{"hx", ft_x_nbr, ft_x_nbrlen, 5, "0x"},
	{"hhx", ft_x_nbr, ft_x_nbrlen, 3, "0x"},
	{"jx", ft_x_lnbr, ft_x_lnbrlen, 9, "0x"},
	{"lx", ft_x_lnbr, ft_x_lnbrlen, 9, "0x"},
	{"llx", ft_x_lnbr, ft_x_lnbrlen, 9, "0x"},
	{"X", ft_x_nbr, ft_x_nbrlen, 7, "0X"},
	{"zX", ft_x_lnbr, ft_x_lnbrlen, 10, "0X"},
	{"hX", ft_x_nbr, ft_x_nbrlen, 5, "0X"},
	{"hhX", ft_x_nbr, ft_x_nbrlen, 3, "0X"},
	{"jX", ft_x_lnbr, ft_x_lnbrlen, 9, "0X"},
	{"lX", ft_x_lnbr, ft_x_lnbrlen, 9, "0X"},
	{"llX", ft_x_lnbr, ft_x_lnbrlen, 9, "0X"},
	{"u", ft_unbr, ft_unbrlen, 7, ""},
	{"zu", ft_ulnbr, ft_ulnbrlen, 10, ""},
	{"hu", ft_unbr, ft_unbrlen, 5, ""},
	{"hhu", ft_unbr, ft_unbrlen, 3, ""},
	{"U", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"lU", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"llU", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"jU", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"zU", ft_ulnbr, ft_ulnbrlen, 10, ""},
	{"hU", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"hhU", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"ju", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"lu", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"llu", ft_ulnbr, ft_ulnbrlen, 9, ""},
	{"c", ft_putchar, ft_ucharlen, 1, ""},
	{"zc", ft_putchar, ft_ucharlen, 1, ""},
	{"jc", ft_putchar, ft_ucharlen, 2, ""},
	{"lc", ft_putchar, ft_ucharlen, 2, ""},
	{"llc", ft_putchar, ft_ucharlen, 1, ""},
	{"hc", ft_putchar, ft_ucharlen, 1, ""},
	{"hhc", ft_putchar, ft_ucharlen, 1, ""},
	{"C", ft_putchar, ft_ucharlen, 2, ""},
	{"zC", ft_putchar, ft_ucharlen, 2, ""},
	{"jC", ft_putchar, ft_ucharlen, 2, ""},
	{"lC", ft_putchar, ft_ucharlen, 2, ""},
	{"llC", ft_putchar, ft_ucharlen, 2, ""},
	{"hC", ft_putchar, ft_ucharlen, 2, ""},
	{"hhC", ft_putchar, ft_ucharlen, 2, ""},
	{"p", ft_x_lnbr, ft_x_lnbrlen, 8, "0x"},
	{"lp", ft_x_lnbr, ft_x_lnbrlen, 8, "0x"},
	{"llp", ft_x_lnbr, ft_x_lnbrlen, 8, "0x"},
	{"hp", ft_x_lnbr, ft_x_lnbrlen, 8, "0x"},
	{"hhp", ft_x_lnbr, ft_x_lnbrlen, 8, "0x"},
	{"zp", ft_x_lnbr, ft_x_lnbrlen, 8, "0x"},
	{"jp", ft_x_lnbr, ft_x_lnbrlen, 8, "0x"},
	{"f", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"Lf", ft_fl_nbr, ft_fl_nbrlen, 14, ""},
	{"lf", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"llf", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"hf", ft_f_nbr, ft_f_nbrlen, 13, ""},
	{"hhf", ft_f_nbr, ft_f_nbrlen, 13, ""},
	{"zf", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"jf", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"F", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"LF", ft_fl_nbr, ft_fl_nbrlen, 14, ""},
	{"lF", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"llF", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"hF", ft_f_nbr, ft_f_nbrlen, 13, ""},
	{"hhF", ft_f_nbr, ft_f_nbrlen, 13, ""},
	{"jF", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"zF", ft_f_nbr, ft_f_nbrlen, 12, ""},
	{"e", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"Le", ft_el_nbr, ft_el_nbrlen, 14, ""},
	{"le", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"lle", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"he", ft_e_nbr, ft_e_nbrlen, 13, ""},
	{"hhe", ft_e_nbr, ft_e_nbrlen, 13, ""},
	{"ze", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"je", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"E", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"LE", ft_el_nbr, ft_el_nbrlen, 14, ""},
	{"lE", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"llE", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"hE", ft_e_nbr, ft_e_nbrlen, 13, ""},
	{"hhE", ft_e_nbr, ft_e_nbrlen, 13, ""},
	{"jE", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"zE", ft_e_nbr, ft_e_nbrlen, 12, ""},
	{"b", ft_bin_nbr, ft_bin_nbrlen, 9, "0b"},
	{"lb", ft_bin_nbr, ft_bin_nbrlen, 9, "0b"},
	{"llb", ft_bin_nbr, ft_bin_nbrlen, 9, "0b"},
	{"hb", ft_bin_nbr, ft_bin_nbrlen, 9, "0b"},
	{"hhb", ft_bin_nbr, ft_bin_nbrlen, 9, "0b"},
	{"zb", ft_bin_nbr, ft_bin_nbrlen, 9, "0b"},
	{"jb", ft_bin_nbr, ft_bin_nbrlen, 9, "0b"},
	{"B", ft_bin_nbr, ft_bin_nbrlen, 9, "0B"},
	{"lB", ft_bin_nbr, ft_bin_nbrlen, 9, "0B"},
	{"llB", ft_bin_nbr, ft_bin_nbrlen, 9, "0B"},
	{"hB", ft_bin_nbr, ft_bin_nbrlen, 9, "0B"},
	{"hhB", ft_bin_nbr, ft_bin_nbrlen, 9, "0B"},
	{"zB", ft_bin_nbr, ft_bin_nbrlen, 9, "0B"},
	{"jB", ft_bin_nbr, ft_bin_nbrlen, 9, "0B"},
	{0, 0, 0, 0, 0}
};

void	set_types(t_conver *conv, t_basic *types, va_list *ap)
{
	types->c = 0;
	conv->size == 1 ? types->c = (char)va_arg(*ap, int) : 0;
	conv->size == 2 ? types->c = va_arg(*ap, int) : 0;
	conv->size == 3 ? types->i = (t_uc)va_arg(*ap, int) : 0;
	conv->size == 4 ? types->i = (char)va_arg(*ap, int) : 0;
	conv->size == 5 ? types->i = (t_ush)va_arg(*ap, int) : 0;
	conv->size == 6 ? types->i = (short)va_arg(*ap, int) : 0;
	conv->size == 7 ? types->i = va_arg(*ap, int) : 0;
	conv->size == 8 ? types->p = va_arg(*ap, void *) : 0;
	conv->size == 9 ? types->im = va_arg(*ap, intmax_t) : 0;
	conv->size == 10 ? types->im = va_arg(*ap, size_t) : 0;
	conv->size == 11 ? types->pd = va_arg(*ap, ptrdiff_t) : 0;
	conv->size == 12 ? types->f = va_arg(*ap, double) : 0;
	conv->size == 13 ? types->f = (float)va_arg(*ap, double) : 0;
	conv->size == 14 ? types->lf = va_arg(*ap, t_ld) : 0;
}

void	ft_free(void)
{
	int i;

	i = 9;
	while (--i >= 0)
		g_f.flags[i] = 0;
	g_f.w = 0;
	g_f.p = 0;
	ft_bzero(g_f.conversion, ft_strlen(g_f.conversion));
	return ;
}

int		arg_zero(t_basic *arg, t_conver *c)
{
	int q;

	q = 0;
	c->size == 1 && arg->c == 0 ? q = 1 : 0;
	c->size == 2 && arg->c == 0 ? q = 1 : 0;
	c->size == 3 && arg->i == 0 ? q = 1 : 0;
	c->size == 4 && arg->i == 0 ? q = 1 : 0;
	c->size == 5 && arg->i == 0 ? q = 1 : 0;
	c->size == 6 && arg->i == 0 ? q = 1 : 0;
	c->size == 7 && arg->i == 0 ? q = 1 : 0;
	c->size <= 7 && arg->i < 0 ? q = -1 : 0;
	c->size == 8 && arg->p == 0 ? q = 1 : 0;
	c->size == 9 && arg->im == 0 ? q = 1 : 0;
	c->size == 9 && arg->im < 0 ? q = -1 : 0;
	c->size == 10 && arg->im == 0 ? q = 1 : 0;
	c->size == 10 && arg->im < 0 ? q = -1 : 0;
	c->size == 11 && arg->pd == 0 ? q = 1 : 0;
	c->size == 11 && arg->pd < 0 ? q = -1 : 0;
	c->size == 12 && arg->f == 0 ? q = 1 : 0;
	c->size == 12 && arg->f < 0 ? q = -1 : 0;
	c->size == 13 && arg->f == 0 ? q = 1 : 0;
	c->size == 13 && arg->f < 0 ? q = -1 : 0;
	c->size == 14 && arg->lf == 0 ? q = 1 : 0;
	c->size == 14 && arg->lf < 0 ? q = -1 : 0;
	return (q);
}

size_t	ft_len_func(t_conver *c, t_basic types, size_t (*func)())
{
	if (c->size < 12)
		return (func(*(void **)&types));
	else if (c->size < 14)
		return (func(*(double *)&types, g_f.p));
	return (func(*(t_ld *)&types, g_f.p));
}

void	ft_wr_func(t_conver *c, t_basic types, void (*func)())
{
	if (c->size < 12)
		func((*(void **)&types), g_f.p);
	else if (c->size < 14)
		func((*(double *)&types), g_f.p);
	else
		func((*(t_ld *)&types), g_f.p);
	return ;
}
