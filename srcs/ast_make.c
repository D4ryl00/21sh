/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:04 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/01 18:07:36 by rbarbero         ###   ########.fr       */
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

t_ast_cmd_name			*ast_cmd_name(t_list **tokens)
{
	t_ast_cmd_name	*name;

	name = NULL;
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(name = (t_ast_cmd_name *)malloc(sizeof(t_ast_cmd_name))))
			exit_perror(ENOMEM, NULL);
		if (!(name->word = ft_strdup(((t_token *)(*tokens)->content)->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
	}
	return (name);
}

t_ast_cmd_word			*ast_cmd_word(t_list **tokens)
{
	t_ast_cmd_word	*word;

	word = NULL;
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(word = (t_ast_cmd_word *)malloc(sizeof(t_ast_cmd_word))))
			exit_perror(ENOMEM, NULL);
		if (!(word->word = ft_strdup(((t_token *)(*tokens)->content)->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
	}
	return (word);
}

t_ast_filename	*ast_filename(t_list **tokens)
{
	t_ast_filename	*filename;

	filename = NULL;
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(filename = (t_ast_filename *)malloc(sizeof(t_ast_filename))))
			exit_perror(ENOMEM, NULL);
		if (!(filename->word = ft_strdup(((t_token *)(*tokens)->content)
						->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
	}
	return (filename);
}

t_ast_io_file	*ast_io_file(t_list **tokens)
{
	t_ast_io_file	*file;
	t_token			*token;

	file = NULL;
	if (*tokens)
	{
		if (!(file = (t_ast_io_file *)malloc(sizeof(t_ast_io_file)))
				|| !(file->op = (t_ast_io_op *)malloc(sizeof(t_ast_io_op))))
			exit_perror(ENOMEM, NULL);
		file->filename = NULL;
		token = (t_token *)(*tokens)->content;
		if ((token->type == LESSAND) || (token->type == GREATAND)
				|| (token->type == DGREAT) || (token->type == LESSGREAT)
				|| (token->type == CLOBBER))
		{
			file->op->c = '\0';
			file->op->e = token->type;
			*tokens = (*tokens)->next;
			file->filename = ast_filename(tokens);
		}
		else if (!ft_strcmp(token->content, "<")
				|| !ft_strcmp(token->content, ">"))
		{
			file->op->c = token->content[0];
			*tokens = (*tokens)->next;
			file->filename = ast_filename(tokens);
		}
		if (!(file->filename))
		{
			free_ast_io_file(file);
			file = NULL;
		}
	}
	return (file);
}

t_ast_here_end		*ast_here_end(t_list **tokens)
{
	t_ast_here_end	*here_end;

	here_end = NULL;
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(here_end = (t_ast_here_end *)malloc(sizeof(t_ast_here_end))))
			exit_perror(ENOMEM, NULL);
		if (!(here_end->word = ft_strdup(((t_token *)(*tokens)->content)->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
	}
	return (here_end);
}

t_ast_io_here		*ast_io_here(t_list **tokens)
{
	t_ast_io_here	*here;

	here = NULL;
	if (*tokens)
	{
		if (!(here = (t_ast_io_here *)malloc(sizeof(t_ast_io_here))))
			exit_perror(ENOMEM, NULL);
		here->here_end = NULL;
		if ((((t_token *)(*tokens)->content)->type == DLESS)
				|| (((t_token *)(*tokens)->content)->type == DLESSDASH))
		{
			here->op = ((t_token *)(*tokens)->content)->type;
			*tokens = (*tokens)->next;
			here->here_end = ast_here_end(tokens);
		}
		if (!(here->here_end))
		{
			free_ast_io_here(here);
			here = NULL;
		}
	}
	return (here);
}

t_ast_io_redirect	*ast_io_redirect(t_list **tokens)
{
	t_ast_io_redirect	*redirect;

	redirect = NULL;
	if (*tokens)
	{
		if (!(redirect = (t_ast_io_redirect *)malloc(
						sizeof(t_ast_io_redirect))))
			exit_perror(ENOMEM, NULL);
		redirect->io_number[0] = '\0';
		redirect->io_file = NULL;
		redirect->io_here = NULL;
		if (((t_token *)(*tokens)->content)->type == IO_NUMBER)
		{
			ft_strncpy(redirect->io_number, ((t_token *)(*tokens)->content)
					->content, IO_NUMBER_SIZE);
			redirect->io_number[3] = '\0';
			*tokens = (*tokens)->next;
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

t_ast_cmd_suffix		*ast_cmd_suffix(t_list **tokens)
{
	t_ast_cmd_suffix	*suffix;

	suffix = NULL;
	if (*tokens)
	{
		if (!(suffix = (struct s_ast_cmd_suffix *)
					malloc(sizeof(struct s_ast_cmd_suffix))))
			exit_perror(ENOMEM, NULL);
		suffix->io_redirect = NULL;
		suffix->word = NULL;
		suffix->cmd_suffix = NULL;
		if (!(suffix->io_redirect = ast_io_redirect(tokens)))
		{
			if ((((t_token *)(*tokens)->content)->type == TOKEN)
					&& (ft_strarrchr(((t_token *)(*tokens)->content)
						->content, g_control_operator) < 0))
			{
				if (!(suffix->word = ft_strdup(((t_token *)(*tokens)->content)
								->content)))
					exit_perror(ENOMEM, NULL);
				*tokens = (*tokens)->next;
			}
		}
		if (suffix->io_redirect || suffix->word)
			suffix->cmd_suffix = ast_cmd_suffix(tokens);
		if (!suffix->io_redirect && !suffix->word)
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
		if (!(prefix->io_redirect = ast_io_redirect(tokens)))
		{
			if (is_assignment_word(((t_token *)(*tokens)->content)->content))
			{
				if (!(prefix->assignment_word =
							ft_strdup(((t_token *)(*tokens)->content)
								->content)))
					exit_perror(ENOMEM, NULL);
				*tokens = (*tokens)->next;
			}
		}
		if (prefix->io_redirect || prefix->assignment_word)
			prefix->cmd_prefix = ast_cmd_prefix(tokens);
		if (!prefix->io_redirect && !prefix->assignment_word)
		{
			free_ast_cmd_prefix(prefix);
			prefix = NULL;
		}
	}
	return (prefix);
}

t_ast_simple_command	*ast_simple_command(t_list **tokens)
{
	t_ast_simple_command	*sc;

	sc = NULL;
	if (*tokens)
	{
		if (!(sc = (t_ast_simple_command *)malloc(sizeof
						(t_ast_simple_command))))
			exit_perror(ENOMEM, NULL);
		sc->cmd_prefix = NULL;
		sc->cmd_word = NULL;
		sc->cmd_name = NULL;
		sc->cmd_suffix = NULL;
		if ((sc->cmd_prefix = ast_cmd_prefix(tokens)))
		{
			if ((sc->cmd_word = ast_cmd_word(tokens)))
				sc->cmd_suffix = ast_cmd_suffix(tokens);
		}
		else if ((sc->cmd_name = ast_cmd_name(tokens)))
			sc->cmd_suffix = ast_cmd_suffix(tokens);
		else
		{
			free_ast_simple_command(sc);
			sc = NULL;
		}
	}
	return (sc);
}

t_ast_command			*ast_command(t_list **tokens)
{
	t_ast_command	*command;

	command = NULL;
	if (*tokens)
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

t_ast_separator_op	*ast_separator_op(t_list **tokens)
{
	t_ast_separator_op	*s_op;

	s_op = NULL;
	if (*tokens)
	{
		if (!(s_op = (t_ast_separator_op *)malloc( sizeof(t_ast_separator_op))))
			exit_perror(ENOMEM, NULL);
		s_op->c = '\0';
		s_op->c = ((t_token *)(*tokens)->content)->content[0];
		if ((s_op->c != '&') && (s_op->c != ';'))
		{
			free_ast_separator_op(s_op);
			s_op = NULL;
		}
		else
			*tokens = (*tokens)->next;
	}
	return (s_op);
}

t_ast_newline_list	*ast_newline_list(t_list **tokens)
{
	t_ast_newline_list	*nl_list;

	nl_list = NULL;
	if (*tokens)
	{
		if (!(nl_list = (t_ast_newline_list *)malloc(
						sizeof(t_ast_newline_list))))
			exit_perror(ENOMEM, NULL);
		nl_list->nl = '\0';
		nl_list->newline_list = NULL;
		if (((t_token *)(*tokens)->content)->content[0] == '\n')
		{
			nl_list->nl = '\n';
			*tokens = (*tokens)->next;
			nl_list->newline_list = ast_newline_list(tokens);
		}
		else
		{
			free_ast_newline_list(nl_list);
			nl_list = NULL;
		}
	}
	return (nl_list);
}

t_ast_linebreak	*ast_linebreak(t_list **tokens)
{
	t_ast_linebreak	*linebreak;

	linebreak = NULL;
	if (*tokens)
	{
		if (!(linebreak = (t_ast_linebreak *)malloc(sizeof(t_ast_linebreak))))
			exit_perror(ENOMEM, NULL);
		linebreak->newline_list = NULL;
		if (!(linebreak->newline_list = ast_newline_list(tokens)))
		{
			free_ast_linebreak(linebreak);
			linebreak = NULL;
		}
	}
	return (linebreak);
}

t_ast_pipe_sequence	*ast_pipe_sequence(t_list **tokens)
{
	t_ast_pipe_sequence	*ps;

	ps = NULL;
	if (*tokens)
	{
		if (!(ps = (t_ast_pipe_sequence *)malloc(sizeof(t_ast_pipe_sequence))))
			exit_perror(ENOMEM, NULL);
		ps->command = NULL;
		ps->linebreak = NULL;
		ps->pipe_sequence = NULL;
		if ((ps->command = ast_command(tokens)))
		{
			if (!ft_strcmp(((t_token *)(*tokens)->content)->content, "|"))
			{
				*tokens = (*tokens)->next;
				ps->linebreak = ast_linebreak(tokens);
				ps->pipe_sequence = ast_pipe_sequence(tokens);
			}
		}
		else
		{
			free_ast_pipe_sequence(ps);
			ps = NULL;
		}
	}
	return (ps);
}

t_ast_pipeline	*ast_pipeline(t_list **tokens)
{
	t_ast_pipeline	*pipeline;

	pipeline = NULL;
	if (*tokens)
	{
		if (!(pipeline = (t_ast_pipeline *)malloc(sizeof(t_ast_pipeline))))
			exit_perror(ENOMEM, NULL);
		pipeline->pipe_sequence = NULL;
		if (!ft_strcmp(((t_token *)(*tokens)->content)->content, "!"))
		{
			pipeline->bang = '!';
			*tokens = (*tokens)->next;
		}
		else
			pipeline->bang = '\0';
		if (!(pipeline->pipe_sequence = ast_pipe_sequence(tokens)))
		{
			free_ast_pipeline(pipeline);
			pipeline = NULL;
		}
	}
	return (pipeline);
}

t_ast_and_or	*ast_and_or(t_list **tokens)
{
	t_ast_and_or	*and_or;

	and_or = NULL;
	if (*tokens)
	{
		if (!(and_or = (t_ast_and_or *)malloc(sizeof(t_ast_and_or))))
			exit_perror(ENOMEM, NULL);
		and_or->pipeline = NULL;
		and_or->linebreak = NULL;
		and_or->and_or = NULL;
		and_or->op = TOKEN;
		if ((and_or->pipeline = ast_pipeline(tokens)))
		{
			if ((((t_token *)(*tokens)->content)->type == AND_IF)
					|| (((t_token *)(*tokens)->content)->type == OR_IF))
			{
				and_or->op = ((t_token *)(*tokens)->content)->type;
				*tokens = (*tokens)->next;
				and_or->linebreak = ast_linebreak(tokens);
				and_or->and_or = ast_and_or(tokens);
			}
		}
		else
		{
			free_ast_and_or(and_or);
			and_or = NULL;
		}
	}
	return (and_or);
}

t_ast_list	*ast_list(t_list **tokens)
{
	t_ast_list	*list;

	list = NULL;
	if (*tokens)
	{
		if (!(list = (t_ast_list *)malloc( sizeof(t_ast_list))))
			exit_perror(ENOMEM, NULL);
		list->and_or = NULL;
		list->separator_op = NULL;
		list->list = NULL;
		if ((list->and_or = ast_and_or(tokens)))
		{
			if ((list->separator_op = ast_separator_op(tokens)))
				list->list = ast_list(tokens);
		}
		else
		{
			free_ast_list(list);
			list = NULL;
		}
	}
	return (list);
}

t_ast_complete_command	*ast_complete_command(t_list **tokens)
{
	t_ast_complete_command	*cc;

	cc = NULL;
	if (*tokens)
	{
		if (!(cc = (t_ast_complete_command *)malloc(
						sizeof(t_ast_complete_command))))
			exit_perror(ENOMEM, NULL);
		cc->list = NULL;
		cc->separator_op = NULL;
		if ((cc->list = ast_list(tokens)))
			cc->separator_op = ast_separator_op(tokens);
		else
		{
			free_ast_complete_command(cc);
			cc = NULL;
		}
	}
	return (cc);
}

t_ast_complete_commands	*ast_complete_commands(t_list **tokens)
{
	t_ast_complete_commands	*cc;

	cc = NULL;
	if (*tokens)
	{
		if (!(cc = (t_ast_complete_commands *)malloc(
						sizeof(t_ast_complete_commands))))
			exit_perror(ENOMEM, NULL);
		cc->complete_command = NULL;
		cc->newline_list = NULL;
		cc->complete_commands = NULL;
		if ((cc->complete_command = ast_complete_command(tokens)))
		{
			if ((cc->newline_list = ast_newline_list(tokens)))
				cc->complete_commands = ast_complete_commands(tokens);
		}
		else
		{
			free_ast_complete_commands(cc);
			cc = NULL;
		}
	}
	return (cc);
}

t_ast_program	*ast_program(t_list *tokens)
{
	t_ast_program	*program;

	program = NULL;
	if (tokens)
	{
		if (!(program = (t_ast_program *)malloc(sizeof(t_ast_program))))
			exit_perror(ENOMEM, NULL);
		program->linebreak = NULL;
		program->complete_commands = NULL;
		program->post_linebreak = NULL;
		program->linebreak = ast_linebreak(&tokens);
		if ((program->complete_commands = ast_complete_commands(&tokens)))
			program->post_linebreak = ast_linebreak(&tokens);
		if (!program->linebreak && !program->complete_commands)
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
