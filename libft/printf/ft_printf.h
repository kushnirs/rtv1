/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 22:25:29 by sergee            #+#    #+#             */
/*   Updated: 2017/12/29 09:23:17 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include "../libft.h"

typedef int				t_wint;
typedef	long double		t_ld;
typedef	unsigned long	t_ul;
typedef	unsigned int	t_ui;
typedef	unsigned char	t_uc;
typedef	unsigned short	t_ush;

# define INF 1.0 / 0.0

/*
** struct t_flags
** 0 1 2 3 4 5 6 7
** - +   # 0 $ L '
*/

typedef struct	s_flags
{
	int		flags[9];
	int		w;
	int		p;
	char	conversion[4];
}				t_flags;

typedef struct	s_conver
{
	char	*conv;
	void	(*wrfunc)();
	t_ul	(*lenf)();
	char	size;
	char	*prefix;
}				t_conver;

typedef union	u_basic
{
	t_wint		c;
	int			i;
	t_ui		ui;
	void		*p;
	t_ld		lf;
	double		f;
	intmax_t	im;
	uintmax_t	uim;
	size_t		z;
	ptrdiff_t	pd;
}				t_basic;

extern	t_flags g_f;
extern	t_conver g_c[];

int				ft_printf(const char *format, ...);
int				arg_zero(t_basic *arg, t_conver *c);
int				ft_nonconv(char *str);
void			ft_free(void);
void			ft_apply_flags(va_list *ap);
void			ft_wr_func(t_conver *c, t_basic types, void (*func)());
void			set_types(t_conver *conv, t_basic *types, va_list *ap);
size_t			ft_len_func(t_conver *c, t_basic types, size_t (*func)());
/*
** decnbr
*/
void			ft_nbr(int n, t_ul i);
void			ft_unbr(t_ui n, t_ul i);
void			ft_lnbr(intmax_t n, t_ul i);
void			ft_ulnbr(uintmax_t n, t_ul i);
size_t			ft_nbrlen(int nbr);
size_t			ft_unbrlen(t_ui nbr);
size_t			ft_lnbrlen(long nbr);
size_t			ft_ulnbrlen(t_ul nbr);
/*
** octnbr
*/
void			ft_o_nbr(t_ui n, t_ul i);
void			ft_o_lnbr(t_ul n, t_ul a);
size_t			ft_o_nbrlen(t_ui n);
size_t			ft_o_lnbrlen(t_ul n);
/*
** hexnbr
*/
void			ft_x_nbr(t_ui n, t_ul a);
void			ft_x_lnbr(uintmax_t n, t_ul a);
size_t			ft_x_nbrlen(t_ui n);
size_t			ft_x_lnbrlen(uintmax_t n);
/*
** doublenbr
*/
void			ft_f_nbr(double n, int i);
void			ft_fl_nbr(t_ld n, int i);
void			ft_e_nbr(double n, int i);
void			ft_el_nbr(t_ld n, int i);
size_t			ft_f_nbrlen(double n, int i);
size_t			ft_fl_nbrlen(t_ld n, int i);
size_t			ft_e_nbrlen(double n, int i);
size_t			ft_el_nbrlen(t_ld n, int i);
/*
** binnbr
*/
void			ft_bin_nbr(uintmax_t n);
size_t			ft_bin_nbrlen(uintmax_t n);

#endif
