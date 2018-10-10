/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsdprintf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 17:05:51 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/10 11:24:24 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VSDPRINTF_H
# define FT_VSDPRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

# define SCHAR signed char
# define UCHAR unsigned char
# define CONV_SPEC "dDiuUoOxXcCsSpnb%"
# define CONV_MOD "hljz"
# define AUTH_CHAR "dDiuUoOxXcCsSpnb.0123456789*$#- +'hljz%"
# define FLAGS_CHAR "#0- +'"

typedef struct	s_seq
{
	size_t	len;
	char	*str;
}				t_seq;

typedef struct	s_conv
{
	int		position;
	UCHAR	hash;
	UCHAR	zero;
	UCHAR	minus;
	UCHAR	space;
	UCHAR	plus;
	UCHAR	quote;
	int		*width;
	UCHAR	dot;
	int		*precision;
	char	modifier[3];
	char	specifier[2];
	void	*data;
	t_seq	*(*fconv)(struct s_conv *conv, intmax_t n);
}				t_conv;

typedef struct	s_arg
{
	int		pos;
	char	type[4];
	void	**data;
}				t_arg;

typedef struct	s_buffer
{
	intmax_t	n;
	t_list		*seq;
}				t_buffer;

intmax_t		ft_vsdprintf(char **str, int fd, const char *format
		, va_list va_args);
intmax_t		ft_dprintf(int fd, const char *format, ...);
intmax_t		ft_sprintf(char **str, const char *format, ...);
intmax_t		ft_printf(const char *format, ...);
void			init_convs(t_conv *convs, int nbr);
t_seq			*init_seq(char *str, size_t len);
t_seq			*print_conv(t_conv *conv, intmax_t n);
UCHAR			parse_format(t_conv *convs, const char *format
		, va_list va_args);
void			parse_position_arg(t_conv *conv, const char **fmt, int *arg_i);
void			parse_flags(t_conv *conv, const char **fmt);
UCHAR			parse_width(t_conv *conv, const char **fmt, t_list **args
		, int *arg_i);
UCHAR			parse_precision(t_conv *conv, const char **fmt, t_list **args
		, int *arg_i);
void			parse_modifier(t_conv *conv, const char **fmt);
UCHAR			parse_specifier(t_conv *conv, const char **fmt);
char			get_specifier(const char *str);
void			get_modifier(char *modifier, const char *str);
UCHAR			new_arg(t_list **args, int pos, const char *type, void **data);
void			take_args(t_list **args, va_list va_args);
void			arg_del(void *content, size_t content_size);
UCHAR			take_int_args(t_list *args, va_list va_args);
UCHAR			take_char_args(t_list *args, va_list va_args);
UCHAR			take_str_args(t_list *args, va_list va_args);
UCHAR			take_n_args(t_list *args, va_list va_args);

t_seq			*int_conv(t_conv *conv, intmax_t n);
char			*int_mod_space(char **str);
char			*int_mod_plus(char **str);
char			*int_mod_quote(char **str);
char			*int_mod_width(char **str, t_conv *conv);
char			*int_mod_precision(char **str, int precision);
t_seq			*uint_conv(t_conv *conv, intmax_t n);
t_seq			*hex_conv(t_conv *conv, intmax_t n);
char			*hex_mod_width(char **str, t_conv *conv);
t_seq			*octal_conv(t_conv *conv, intmax_t n);
t_seq			*bin_conv(t_conv *conv, intmax_t n);
char			*bin_mod_width(char **str, t_conv *conv);
t_seq			*char_conv(t_conv *conv, intmax_t n);
t_seq			*str_conv(t_conv *conv, intmax_t n);
t_seq			*percent_conv(t_conv *conv, intmax_t n);
t_seq			*n_conv(t_conv *conv, intmax_t n);
t_seq			*default_conv(t_conv *conv, intmax_t n);
UCHAR			buf_add_str(t_buffer *buf, char *str);
UCHAR			buf_add_seq(t_buffer *buf, t_seq *seq);
UCHAR			buf_print(char **str, int fd, t_buffer *buf);
UCHAR			print_color(t_buffer *buf, const char **fmt);
#endif
