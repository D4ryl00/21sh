/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:13:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/15 22:24:44 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include "get_next_line.h"
# include "ft_vsdprintf.h"
# include <wchar.h>
# include <stdint.h>

# define BUFFER_SIZE 4096

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_btree
{
	void			*content;
	size_t			content_size;
	struct s_btree	*left;
	struct s_btree	*right;
}				t_btree;

typedef struct	s_buf
{
	char	*buf;
	long	i;
	long	size;
}				t_buf;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle
							, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strpushback(char **str, char c);
int				ft_atoi(const char *str);
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isstrdigit(char *str);
void			ft_strtoupper(char *s);
void			ft_strtolower(char *s);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_strnclr(char *s, int len);
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
char			**ft_strsplitstr(char const *s, char *tokens);
t_list			*ft_strnarrtolist(char **arr, int len);
t_list			*ft_strarrtolist(char **arr);
void			ft_strarrdel(char **arr);
int				ft_absolute(int nbr);
char			*ft_itoa(int n);
int				ft_nbrlen(intmax_t n);
char			*ft_imtoa_base(intmax_t n, int base);
char			*ft_uimtoa_base(uintmax_t n, int base);
int				ft_putchar(int c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
int				ft_putchar_fd(int c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddback(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_strsplittolst(char const *s, char c);
t_list			*ft_lstnewnode(t_list **lst, void *content
								, size_t content_size);
t_list			*ft_lstpushback(t_list **begin_list, void *content
								, size_t content_size);
int				ft_lstsize(t_list *begin_list);
t_list			*ft_lstsortedinsert(t_list **list, t_list *node
								, int (*cmp)(t_list *, t_list *));
t_list			*ft_lstrsortedinsert(t_list **list, t_list *node
								, int (*cmp)(t_list *, t_list *));
void			ft_lstdelnode(t_list **previous, t_list *node
		, void (*del)(void *, size_t));
void			ft_lstdelif(t_list **list, void *data
		, int (*test)(t_list *, void *), void (*del)(void *, size_t));
t_list			*ft_lstselect(t_list *list, void *data
		, int (*test)(t_list *, void *));
unsigned int	ft_char_encode_utf8(unsigned int c);
unsigned int	ft_char_decode_utf8(unsigned int c);
int				ft_is_valid_unicode(wint_t wchar);
int				ft_wctomb(char *s, wchar_t wchar);
size_t			ft_wcslen(const wchar_t *s);
char			*ft_getfilename(char *path);
int				ft_buf_init(t_buf *buffer);
char			*ft_buf_flush(t_buf *buffer);
int				ft_buf_extend(t_buf *buffer);
int				ft_buf_add_char(t_buf *buffer, char c);
int				ft_buf_insert_char(t_buf *buffer, char c, int index);
int				ft_buf_delete_char(t_buf *buffer, int index);
void			ft_buf_destroy(t_buf *buffer);
t_btree			*ft_btreenew(void const *content, size_t content_size);
void			ft_btreedelone(t_btree **abtree, void (*del)(void *, size_t));
void			ft_btreedel(t_btree **abtree, void (*del)(void *, size_t));

#endif
