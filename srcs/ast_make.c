/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:04 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/28 13:55:53 by rbarbero         ###   ########.fr       */
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
	if (sc && sc->cmd_word && sc->cmd_word->word)
		return (sc->cmd_word->word);
	if (sc && sc->cmd_name && sc->cmd_name->word)
		return (sc->cmd_name->word);
	else
		return (NULL);
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

t_ast_cmd_word			*ast_cmd_word(t_list *tokens)
{
	t_ast_cmd_word	*word;

	word = NULL;
	if (tokens && ((t_token *)tokens->content)->type == TOKEN)
	{
		if (!(word = (t_ast_cmd_word *)malloc(sizeof(t_ast_cmd_word))))
			exit_perror(ENOMEM, NULL);
		if (!(word->word = ft_strdup(((t_token *)tokens->content)->content)))
			exit_perror(ENOMEM, NULL);
	}
	return (word);
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
	t_token			*token;

	file = NULL;
	if (tokens)
	{
		if (!(file = (t_ast_io_file *)malloc(sizeof(t_ast_io_file)))
				|| !(file->op = (t_ast_io_op *)malloc(sizeof(t_ast_io_op))))
			exit_perror(ENOMEM, NULL);
		file->filename = NULL;
		token = (t_token *)tokens->content;
		if ((token->type == LESSAND) || (token->type == GREATAND)
				|| (token->type == DGREAT) || (token->type == LESSGREAT)
				|| (token->type == CLOBBER))
		{
			file->op->c = '\0';
			file->op->e = token->type;
			file->filename = ast_filename(tokens->next);
		}
		else if (!ft_strcmp(token->content, "<")
				|| !ft_strcmp(token->content, ">"))
		{
			file->op->c = token->content[0];
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

t_ast_here_end		*ast_here_end(t_list *tokens)
{
	t_ast_here_end	*here_end;

	here_end = NULL;
	if (tokens && ((t_token *)tokens->content)->type == TOKEN)
	{
		if (!(here_end = (t_ast_here_end *)malloc(sizeof(t_ast_here_end))))
			exit_perror(ENOMEM, NULL);
		if (!(here_end->word = ft_strdup(((t_token *)tokens->content)->content)))
			exit_perror(ENOMEM, NULL);
	}
	return (here_end);
}

t_ast_io_here		*ast_io_here(t_list *tokens)
{
	t_ast_io_here	*here;

	here = NULL;
	if (tokens)
	{
		if (!(here = (t_ast_io_here *)malloc(sizeof(t_ast_io_here))))
			exit_perror(ENOMEM, NULL);
		here->here_end = NULL;
		if ((((t_token *)tokens->content)->type == DLESS)
				|| (((t_token *)tokens->content)->type == DLESSDASH))
		{
			here->op = ((t_token *)tokens->content)->type;
			here->here_end = ast_here_end(tokens->next);
		}
		if (!(here->here_end))
		{
			free_ast_io_here(here);
			here = NULL;
		}
	}
	return (here);
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
			ft_strncpy(redirect->io_number, ((t_token *)tokens->content)->content, IO_NUMBER_SIZE);
			redirect->io_number[3] = '\0';
			tokens = tokens->next;
		}
		if (!(redirect->io_file = ast_io_file(tokens))
				&& !(redirect->io_here = ast_io_here(tokens)))
		{
			free_ast_io_redirect(redirect);
			redirect = NULL;
		}
	}
	return (redirect);
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
			if (suffix->io_redirect->io_number[0])
				suffix->cmd_suffix = ast_cmd_suffix(tokens->next->next->next);
			else
				suffix->cmd_suffix = ast_cmd_suffix(tokens->next->next);
		}
		else if (((t_token *)tokens->content)->type == TOKEN)
		{
			if (!(suffix->word = ft_strdup(((t_token *)tokens->content)
							->content)))
				exit_perror(ENOMEM, NULL);
			suffix->cmd_suffix = ast_cmd_suffix(tokens->next);
		}
		else
		{
			free_ast_cmd_suffix(suffix);
			suffix = NULL;
		}
	}
	return (suffix);
}

int						is_valid_name(char *str)
{
	if (!*str || ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (*str != '_' && !ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

int						is_assignment_word(char *str)
{
	char	*equal;
	char	*name;

	if ((equal = ft_strchr(str, '=')))
	{
		if (*str == '=')
			return (0);
		if (!(name = ft_strndup(str, equal - str)))
			exit_perror(ENOMEM, NULL);
		if (is_valid_name(name))
			return (1);
	}
	return (0);
}

t_ast_cmd_prefix		*ast_cmd_prefix(t_list	**tokens)
{
	t_ast_cmd_prefix	*prefix;

	prefix = NULL;
	if (*tokens)
	{
		if (!(prefix = (struct s_ast_cmd_prefix *)
					malloc(sizeof(struct s_ast_cmd_prefix))))
			exit_perror(ENOMEM, NULL);
		prefix->io_redirect = NULL;
		prefix->assignment_word = NULL;
		prefix->cmd_prefix = NULL;
		if ((prefix->io_redirect = ast_io_redirect(*tokens)))
		{
			if (prefix->io_redirect->io_number[0])
				*tokens = (*tokens)->next->next->next;
			else
				*tokens = (*tokens)->next->next;
			prefix->cmd_prefix = ast_cmd_prefix(tokens);
		}
		else if (is_assignment_word(((t_token *)(*tokens)->content)->content))
		{
			if (!(prefix->assignment_word =
						ft_strdup(((t_token *)(*tokens)->content)
							->content)))
				exit_perror(ENOMEM, NULL);
			*tokens = (*tokens)->next;
			prefix->cmd_prefix = ast_cmd_prefix(tokens);
		}
		else
		{
			free_ast_cmd_prefix(prefix);
			prefix = NULL;
		}
	}
	return (prefix);
}

t_ast_simple_command	*ast_simple_command(t_list *tokens)
{
	t_ast_simple_command	*sc;

	sc = NULL;
	if (tokens)
	{
		if (!(sc = (t_ast_simple_command *)malloc(sizeof
						(t_ast_simple_command))))
			exit_perror(ENOMEM, NULL);
		sc->cmd_prefix = NULL;
		sc->cmd_word = NULL;
		sc->cmd_name = NULL;
		sc->cmd_suffix = NULL;
		if ((sc->cmd_prefix = ast_cmd_prefix(&tokens)))
		{
			if ((sc->cmd_word = ast_cmd_word(tokens)))
				sc->cmd_suffix = ast_cmd_suffix(tokens->next);
		}
		else if ((sc->cmd_name = ast_cmd_name(tokens)))
			sc->cmd_suffix = ast_cmd_suffix(tokens->next);
		else
		{
			free_ast_simple_command(sc);
			sc = NULL;
		}
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
			ft_printf("21sh: parse error near `%s\n'", ((t_token *)tokens->content)->content);
	}
	return (program);
}
