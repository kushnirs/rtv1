/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 17:42:31 by skushnir          #+#    #+#             */
/*   Updated: 2018/03/02 10:14:30 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

extern	size_t	g_symb;

void			*ft_memset(void *memptr, int val, size_t num);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *destptr, const void *srcptr, size_t num);
void			*ft_memccpy(void *dest, const void *source, int ch,
							size_t count);
void			*ft_memmove(void *destptr, const void *srcptr, size_t num);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *memptr1, const void *memptr2, size_t num);
size_t			ft_strlen(const char *string);
size_t			ft_strulen(const int *string);
size_t			ft_strunlen(const int *string, size_t n);
size_t			ft_strnlen(const char *string, size_t n);
char			*ft_strdup(const char *src);
char			*ft_strcpy(char *destptr, const char *srcptr);
char			*ft_strncpy(char *destptr, const char *srcptr, size_t num);
char			*ft_strcat(char *destptr, const char *srcptr);
char			*ft_strncat(char *destptr, char *srcptr, size_t num);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *string, int symbol);
char			*ft_strrchr(const char *string, int symbol);
char			*ft_strstr(const char *string1, const char *string2);
char			*ft_strnstr(const char *string1, const char *string2,
							size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strpcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
void			ft_putchar(int c);
char			*ft_itoa(int n);
void			ft_putstr(char const *s);
void			ft_putunstr(int const *s, size_t n);
void			ft_putnstr(char const *s, size_t n);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(int c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char			*ft_strrev(char *str);
void			ft_putnstr(char const *s, size_t n);
size_t			ft_ucharlen(int c);
int				get_next_line(const int fd, char **line);
double			ft_pow(double i, double a);
long			ft_hex_to_dec(char *str);

#endif
