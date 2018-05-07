/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:34:06 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/05 08:52:17 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "../libft/includes/libft.h"

# define BUF_SIZ 10

enum			e_type
{
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER
};

typedef struct	s_token
{
	enum e_type	type;
	char		*content;
}				t_token;

enum			e_op_type
{
	AND_IF,
	O_RIF,
	DSEMI,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	CLOBBER
};

typedef struct	s_op_token
{
	enum e_op_type	type;
	char			*content;
	void			*op;
}				t_op_token;

extern char		*g_op_token [];

enum			e_errno
{
	ENOMEM,
	enocmd,
	enoent,
	eacces,
	EOTHER
};

typedef struct	s_input
{
	char	*str;
	char	*save;
}				t_input;

extern char		*g_errors[];

void			exit_perror(enum e_errno num, char *str);
int				return_perror(enum e_errno num, char *str);
int				prompt(t_input *input, char *prompt);
t_btree			*eval(t_btree *ast, t_input *input);
t_list			*get_tokens(t_input *input);
void			token_free(void *content, size_t size);

#endif
