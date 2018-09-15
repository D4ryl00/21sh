/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:04 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/16 01:28:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include <stdlib.h>

/*
** For a simple_command, return the command name for execve
*/
char	*ast_get_cmd_name(t_ast_simple_command *sc)
{
	if (sc && sc->cmd_name && sc->cmd_name->word)
		return (sc->cmd_name->word);
	else
		return (NULL);
}

/*
** For a simple_command, return the number of arguments of the command.
*/
static int	ast_get_cmd_args_size(t_ast_simple_command *sc)
{
	int	size;
	t_ast_cmd_suffix	*suffix;

	size = 0;
	suffix = sc->cmd_suffix;
	while (suffix)
	{
		if (suffix->word)
			size++;
		suffix = suffix->cmd_suffix;
	}
	return (size);
}

/*
** For a simple_command, return an array of string with arguments
** of the command for execve. It's begin by the command name
** and terminate by a NULL pointer.
*/
char	**ast_construct_cmd_args(t_ast_simple_command *sc)
{
	char				**args;
	int					size;
	int					i;
	t_ast_cmd_suffix	*suffix;

	args = NULL;
	size = ast_get_cmd_args_size(sc) + 1;
	if (!(args = (char **)malloc(sizeof(char *) * size + 1)))
		exit_perror(ENOMEM, NULL);
	args[0] = ft_strdup(ast_get_cmd_name(sc));
	i = 1;
	suffix = sc->cmd_suffix;
	while (suffix)
	{
		if (suffix->word)
		{
			if (!(args[i++] = ft_strdup(suffix->word)))
				exit_perror(ENOMEM, NULL);
		}
		suffix = suffix->cmd_suffix;
	}
	args[size] = NULL;
	return (args);
}

t_ast_cmd_name			*ast_cmd_name(t_list *tokens)
{
	t_ast_cmd_name	*name;

	name = NULL;
	if (tokens && ((t_token *)tokens->content)->type == TOKEN)
	{
		if (!(name = (t_ast_cmd_name *)malloc(sizeof(t_ast_cmd_name))))
			exit_perror(ENOMEM, NULL);
		if (!(name->word = ft_strdup(((t_token *)tokens->content)->content)))
			exit_perror(ENOMEM, NULL);
	}
	return (name);
}

t_ast_filename	*ast_filename(t_list *tokens)
{
	t_ast_filename	*filename;

	filename = NULL;
	if (tokens && ((t_token *)tokens->content)->type == TOKEN)
	{
		if (!(filename = (t_ast_filename *)malloc(sizeof(t_ast_filename))))
			exit_perror(ENOMEM, NULL);
		if (!(filename->word = ft_strdup(((t_token *)tokens->content)->content)))
			exit_perror(ENOMEM, NULL);
	}
	return (filename);
}

t_ast_io_file	*ast_io_file(t_list *tokens)
{
	t_ast_io_file	*file;

	file = NULL;
	if (tokens)
	{
		if (!(file = (t_ast_io_file *)malloc(sizeof(t_ast_io_file))))
			exit_perror(ENOMEM, NULL);
		file->operator[0] = '\0';
		file->filename = NULL;
		if (!ft_strcmp(((t_token *)tokens->content)->content, "<") ||
				!ft_strcmp(((t_token *)tokens->content)->content, "<&") ||
				!ft_strcmp(((t_token *)tokens->content)->content, ">") ||
				!ft_strcmp(((t_token *)tokens->content)->content, ">&") ||
				!ft_strcmp(((t_token *)tokens->content)->content, ">>") ||
				!ft_strcmp(((t_token *)tokens->content)->content, "<>") ||
				!ft_strcmp(((t_token *)tokens->content)->content, ">|"))
		{
			ft_strncpy(file->operator, ((t_token *)tokens->content)->content, 3);
			file->filename = ast_filename(tokens->next);
		}
		if (!(file->filename))
		{
			free_ast_io_file(file);
			file = NULL;
		}
	}
	return (file);
}

t_ast_io_redirect	*ast_io_redirect(t_list *tokens)
{
	t_ast_io_redirect	*redirect;

	redirect = NULL;
	if (tokens)
	{
		if (!(redirect = (t_ast_io_redirect *)malloc(sizeof(t_ast_io_redirect))))
			exit_perror(ENOMEM, NULL);
		redirect->io_number[0] = '\0';
		redirect->io_file = NULL;
		redirect->io_here = NULL;
		if (((t_token *)tokens->content)->type == IO_NUMBER)
		{
			ft_strncpy(redirect->io_number, ((t_token *)tokens->content)->content, 3);
			tokens = tokens->next;
		}
		if (!(redirect->io_file = ast_io_file(tokens)))
		{
			free_ast_io_redirect(redirect);
			redirect = NULL;
		}
	}
	return (redirect);
}

struct s_ast_cmd_suffix	*ast_cmd_suffix_r(t_list *tokens)
{
	struct s_ast_cmd_suffix	*suffix;

	suffix = NULL;
	if (tokens)
	{
		if (!(suffix = (struct s_ast_cmd_suffix *)
					malloc(sizeof(struct s_ast_cmd_suffix))))
			exit_perror(ENOMEM, NULL);
		suffix->io_redirect = NULL;
		suffix->word = NULL;
		suffix->cmd_suffix = NULL;
		if ((suffix->io_redirect = ast_io_redirect(tokens)))
		{
			/*if (!(suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next)))
			{
				free_ast_io_redirect(suffix->io_redirect);
				suffix->io_redirect = NULL;
			}*/
			if (suffix->io_redirect->io_number[0])
				suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next->next->next);
			else
				suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next->next);
		}
		else if (!suffix->io_redirect && ((t_token *)tokens->content)->type == TOKEN)
		{
			if (!(suffix->word = ft_strdup(((t_token *)tokens->content)->content)))
				exit_perror(ENOMEM, NULL);
			/*if (!(suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next)))
			{
				free(suffix->word);
				suffix->word = NULL;
			}*/
			suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next);
		}
		if (!(suffix->io_redirect) && !(suffix->word))
		{
			free_ast_cmd_suffix(suffix);
			suffix = NULL;
		}
	}
	return (suffix);
}

t_ast_cmd_suffix		*ast_cmd_suffix(t_list *tokens)
{
	t_ast_cmd_suffix	*suffix;

	suffix = NULL;
	if (tokens)
	{
		if (!(suffix = (struct s_ast_cmd_suffix *)
					malloc(sizeof(struct s_ast_cmd_suffix))))
			exit_perror(ENOMEM, NULL);
		suffix->io_redirect = NULL;
		suffix->word = NULL;
		suffix->cmd_suffix = NULL;
		if ((suffix->io_redirect = ast_io_redirect(tokens)))
		{
			/*if (!(suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next)))
			{
				free_ast_io_redirect(suffix->io_redirect);
				suffix->io_redirect = NULL;
			}*/
			suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next);
		}
		else if (!suffix->io_redirect && ((t_token *)tokens->content)->type == TOKEN)
		{
			if (!(suffix->word = ft_strdup(((t_token *)tokens->content)->content)))
				exit_perror(ENOMEM, NULL);
			/*if (!(suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next)))
			{
				free(suffix->word);
				suffix->word = NULL;
			}*/
			suffix->cmd_suffix = ast_cmd_suffix_r(tokens->next);
		}
		if (!(suffix->io_redirect) && !(suffix->word))
		{
			free_ast_cmd_suffix(suffix);
			suffix = NULL;
		}
	}
	return (suffix);
}

t_ast_simple_command	*ast_simple_command(t_list *tokens)
{
	t_ast_simple_command	*sc;

	sc = NULL;
	if (tokens)
	{
		if (!(sc = (t_ast_simple_command *)malloc(sizeof(t_ast_simple_command))))
			exit_perror(ENOMEM, NULL);
		sc->cmd_name = NULL;
		sc->cmd_suffix = NULL;
		if ((sc->cmd_name = ast_cmd_name(tokens)))
			sc->cmd_suffix = ast_cmd_suffix(tokens->next);
		else
			free_ast_simple_command(sc);
	}
	return (sc);
}

t_ast_command			*ast_command(t_list *tokens)
{
	t_ast_command	*command;

	command = NULL;
	if (tokens)
	{
		if (!(command = (t_ast_command *)malloc(sizeof(t_ast_command))))
			exit_perror(ENOMEM, NULL);
		command->simple_command = NULL;
		command->redirect_list = NULL;
		if (!(command->simple_command = ast_simple_command(tokens)))
		{
			free_ast_command(command);
			command = NULL;
		}
	}
	return (command);
}

t_ast_program	*ast_program(t_list *tokens)
{
	t_ast_program	*program;

	program = NULL;
	if (tokens)
	{
		if (!(program = (t_ast_program *)malloc(sizeof(t_ast_program))))
			exit_perror(ENOMEM, NULL);
		// ici tester les différentes solutions, et si aucune, alors free
		if (!(program->command = ast_command(tokens)))
		{
			free_ast_program(program);
			program = NULL;
		}
	}
	return (program);
}

t_ast_program	*make_ast(t_list *tokens)
{
	t_ast_program	*program;

	program = NULL;
	if (tokens)
	{
		if (!(program = ast_program(tokens)))
			ft_printf("21sh: parse error near `%s\n'", tokens->content);
	}
	return (program);
}
