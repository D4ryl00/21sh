/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:04 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/03 14:37:39 by rbarbero         ###   ########.fr       */
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

int	ast_cmd_name(t_ast_cmd_name **name, t_list **tokens)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(*name = (t_ast_cmd_name *)malloc(sizeof(t_ast_cmd_name))))
			exit_perror(ENOMEM, NULL);
		if (!((*name)->word = ft_strdup(((t_token *)(*tokens)->content)->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
		return (1);
	}
	return (0);
}

int	ast_cmd_word(t_ast_cmd_word **word, t_list **tokens)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(*word = (t_ast_cmd_word *)malloc(sizeof(t_ast_cmd_word))))
			exit_perror(ENOMEM, NULL);
		if (!((*word)->word = ft_strdup(((t_token *)(*tokens)->content)->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
		return (1);
	}
	return (0);
}

int	ast_filename(t_ast_filename **filename, t_list **tokens)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(*filename = (t_ast_filename *)malloc(sizeof(t_ast_filename))))
			exit_perror(ENOMEM, NULL);
		if (!((*filename)->word = ft_strdup(((t_token *)(*tokens)->content)
						->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
		return (1);
	}
	return (0);
}

int	ast_io_file(t_ast_io_file **file, t_list **tokens)
{
	t_token			*token;

	if (*tokens)
	{
		if (!(*file = (t_ast_io_file *)malloc(sizeof(t_ast_io_file)))
				|| !((*file)->op = (t_ast_io_op *)malloc(sizeof(t_ast_io_op))))
			exit_perror(ENOMEM, NULL);
		(*file)->filename = NULL;
		token = (t_token *)(*tokens)->content;
		if ((token->type == LESSAND) || (token->type == GREATAND)
				|| (token->type == DGREAT) || (token->type == LESSGREAT)
				|| (token->type == CLOBBER))
		{
			(*file)->op->c = '\0';
			(*file)->op->e = token->type;
			*tokens = (*tokens)->next;
			ast_filename(&((*file)->filename), tokens);
		}
		else if (!ft_strcmp(token->content, "<")
				|| !ft_strcmp(token->content, ">"))
		{
			(*file)->op->c = token->content[0];
			*tokens = (*tokens)->next;
			ast_filename(&((*file)->filename), tokens);
		}
		if (!((*file)->filename))
		{
			free_ast_io_file(*file);
			*file = NULL;
			return (0);
		}
		return (1);
	}
	return (0);
}

int	ast_here_end(t_ast_here_end **here_end, t_list **tokens)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(*here_end = (t_ast_here_end *)malloc(sizeof(t_ast_here_end))))
			exit_perror(ENOMEM, NULL);
		if (!((*here_end)->word = ft_strdup(((t_token *)(*tokens)->content)->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
		return (1);
	}
	return (0);
}

int	ast_io_here(t_ast_io_here **here, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*here = (t_ast_io_here *)malloc(sizeof(t_ast_io_here))))
			exit_perror(ENOMEM, NULL);
		(*here)->here_end = NULL;
		if ((((t_token *)(*tokens)->content)->type == DLESS)
				|| (((t_token *)(*tokens)->content)->type == DLESSDASH))
		{
			(*here)->op = ((t_token *)(*tokens)->content)->type;
			*tokens = (*tokens)->next;
			ast_here_end(&((*here)->here_end), tokens);
		}
		if (!((*here)->here_end))
		{
			free_ast_io_here(*here);
			*here = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_io_redirect(t_ast_io_redirect **redirect, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*redirect = (t_ast_io_redirect *)malloc(
						sizeof(t_ast_io_redirect))))
			exit_perror(ENOMEM, NULL);
		(*redirect)->io_number[0] = '\0';
		(*redirect)->io_file = NULL;
		(*redirect)->io_here = NULL;
		if (((t_token *)(*tokens)->content)->type == IO_NUMBER)
		{
			ft_strncpy((*redirect)->io_number, ((t_token *)(*tokens)->content)
					->content, IO_NUMBER_SIZE);
			(*redirect)->io_number[3] = '\0';
			*tokens = (*tokens)->next;
		}
		if (!(ast_io_file(&((*redirect)->io_file), tokens))
				&& !(ast_io_here(&((*redirect)->io_here), tokens)))
		{
			free_ast_io_redirect(*redirect);
			*redirect = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_cmd_suffix(t_ast_cmd_suffix **suffix, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*suffix = (struct s_ast_cmd_suffix *)
					malloc(sizeof(struct s_ast_cmd_suffix))))
			exit_perror(ENOMEM, NULL);
		(*suffix)->io_redirect = NULL;
		(*suffix)->word = NULL;
		(*suffix)->cmd_suffix = NULL;
		if (!(ast_io_redirect(&((*suffix)->io_redirect), tokens)))
		{
			if ((((t_token *)(*tokens)->content)->type == TOKEN)
					&& (((t_token *)(*tokens)->content)->type != CONTROL))
			{
				if (!((*suffix)->word = ft_strdup(((t_token *)(*tokens)->content)
								->content)))
					exit_perror(ENOMEM, NULL);
				*tokens = (*tokens)->next;
			}
		}
		if ((*suffix)->io_redirect || (*suffix)->word)
			ast_cmd_suffix(&((*suffix)->cmd_suffix), tokens);
		if (!(*suffix)->io_redirect && !(*suffix)->word)
		{
			free_ast_cmd_suffix(*suffix);
			*suffix = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
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

int	ast_cmd_prefix(t_ast_cmd_prefix **prefix, t_list	**tokens)
{
	if (*tokens)
	{
		if (!(*prefix = (struct s_ast_cmd_prefix *)
					malloc(sizeof(struct s_ast_cmd_prefix))))
			exit_perror(ENOMEM, NULL);
		(*prefix)->io_redirect = NULL;
		(*prefix)->assignment_word = NULL;
		(*prefix)->cmd_prefix = NULL;
		if (!(ast_io_redirect(&((*prefix)->io_redirect), tokens)))
		{
			if (is_assignment_word(((t_token *)(*tokens)->content)->content))
			{
				if (!((*prefix)->assignment_word =
							ft_strdup(((t_token *)(*tokens)->content)
								->content)))
					exit_perror(ENOMEM, NULL);
				*tokens = (*tokens)->next;
			}
		}
		if ((*prefix)->io_redirect || (*prefix)->assignment_word)
			ast_cmd_prefix(&((*prefix)->cmd_prefix), tokens);
		if (!(*prefix)->io_redirect && !(*prefix)->assignment_word)
		{
			free_ast_cmd_prefix(*prefix);
			*prefix = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_simple_command(t_ast_simple_command **sc, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*sc = (t_ast_simple_command *)malloc(sizeof
						(t_ast_simple_command))))
			exit_perror(ENOMEM, NULL);
		(*sc)->cmd_prefix = NULL;
		(*sc)->cmd_word = NULL;
		(*sc)->cmd_name = NULL;
		(*sc)->cmd_suffix = NULL;
		if ((ast_cmd_prefix(&((*sc)->cmd_prefix), tokens)))
		{
			if (ast_cmd_word(&((*sc)->cmd_word), tokens))
				ast_cmd_suffix(&((*sc)->cmd_suffix), tokens);
		}
		else if (ast_cmd_name(&((*sc)->cmd_name), tokens))
			ast_cmd_suffix(&((*sc)->cmd_suffix), tokens);
		else
		{
			free_ast_simple_command(*sc);
			*sc = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_command(t_ast_command **command, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*command = (t_ast_command *)malloc(sizeof(t_ast_command))))
			exit_perror(ENOMEM, NULL);
		(*command)->simple_command = NULL;
		(*command)->redirect_list = NULL;
		if (!(ast_simple_command(&((*command)->simple_command), tokens)))
		{
			free_ast_command(*command);
			*command = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_separator_op(t_ast_separator_op **s_op, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*s_op = (t_ast_separator_op *)malloc( sizeof(t_ast_separator_op))))
			exit_perror(ENOMEM, NULL);
		(*s_op)->c = ((t_token *)(*tokens)->content)->content[0];
		if (((*s_op)->c != '&') && ((*s_op)->c != ';'))
		{
			free_ast_separator_op(*s_op);
			*s_op = NULL;
			return (0);
		}
		*tokens = (*tokens)->next;
		return (1);
	}
	return (-1);
}

int	ast_newline_list(t_ast_newline_list **nl_list, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*nl_list = (t_ast_newline_list *)malloc(
						sizeof(t_ast_newline_list))))
			exit_perror(ENOMEM, NULL);
		(*nl_list)->nl = '\0';
		(*nl_list)->newline_list = NULL;
		if (((t_token *)(*tokens)->content)->content[0] == '\n')
		{
			(*nl_list)->nl = '\n';
			*tokens = (*tokens)->next;
			ast_newline_list(&((*nl_list)->newline_list), tokens);
		}
		else
		{
			free_ast_newline_list(*nl_list);
			*nl_list = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_linebreak(t_ast_linebreak **linebreak, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*linebreak = (t_ast_linebreak *)malloc(sizeof(t_ast_linebreak))))
			exit_perror(ENOMEM, NULL);
		(*linebreak)->newline_list = NULL;
		if (!ast_newline_list(&((*linebreak)->newline_list), tokens))
		{
			free_ast_linebreak(*linebreak);
			*linebreak = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_pipe_sequence(t_ast_pipe_sequence **ps, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*ps = (t_ast_pipe_sequence *)malloc(sizeof(t_ast_pipe_sequence))))
			exit_perror(ENOMEM, NULL);
		(*ps)->command = NULL;
		(*ps)->linebreak = NULL;
		(*ps)->pipe_sequence = NULL;
		if (ast_command(&((*ps)->command), tokens))
		{
			if (!ft_strcmp(((t_token *)(*tokens)->content)->content, "|"))
			{
				*tokens = (*tokens)->next;
				ast_linebreak(&((*ps)->linebreak), tokens);
				if (!ast_pipe_sequence(&((*ps)->pipe_sequence), tokens))
				{
					ft_perror(ESYNT, ((t_token *)(*tokens)->content)->content);
					free_ast_pipe_sequence(*ps);
					*ps = NULL;
					return (-1);
				}
			}
		}
		else
		{
			free_ast_pipe_sequence(*ps);
			*ps = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_pipeline(t_ast_pipeline **pipeline, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*pipeline = (t_ast_pipeline *)malloc(sizeof(t_ast_pipeline))))
			exit_perror(ENOMEM, NULL);
		(*pipeline)->pipe_sequence = NULL;
		if (!ft_strcmp(((t_token *)(*tokens)->content)->content, "!"))
		{
			(*pipeline)->bang = '!';
			*tokens = (*tokens)->next;
		}
		else
			(*pipeline)->bang = '\0';
		if (!ast_pipe_sequence(&((*pipeline)->pipe_sequence), tokens))
		{
			free_ast_pipeline(*pipeline);
			*pipeline = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_and_or(t_ast_and_or **and_or, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*and_or = (t_ast_and_or *)malloc(sizeof(t_ast_and_or))))
			exit_perror(ENOMEM, NULL);
		(*and_or)->pipeline = NULL;
		(*and_or)->linebreak = NULL;
		(*and_or)->and_or = NULL;
		(*and_or)->op = TOKEN;
		if (ast_pipeline(&((*and_or)->pipeline), tokens))
		{
			if ((((t_token *)(*tokens)->content)->type == AND_IF)
					|| (((t_token *)(*tokens)->content)->type == OR_IF))
			{
				(*and_or)->op = ((t_token *)(*tokens)->content)->type;
				*tokens = (*tokens)->next;
				ast_linebreak(&((*and_or)->linebreak), tokens);
				if (!ast_and_or(&((*and_or)->and_or), tokens))
				{
					ft_perror(ESYNT, ((t_token *)(*tokens)->content)->content);
					free_ast_and_or(*and_or);
					*and_or = NULL;
					return (-1);
				}
			}
		}
		else
		{
			free_ast_and_or(*and_or);
			*and_or = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_list(t_ast_list **list, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*list = (t_ast_list *)malloc( sizeof(t_ast_list))))
			exit_perror(ENOMEM, NULL);
		(*list)->and_or = NULL;
		(*list)->separator_op = NULL;
		(*list)->list = NULL;
		if (ast_and_or(&((*list)->and_or), tokens))
		{
			if (ast_separator_op(&((*list)->separator_op), tokens))
				ast_list(&((*list)->list), tokens);
		}
		else
		{
			free_ast_list(*list);
			*list = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_complete_command(t_ast_complete_command **cc, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*cc = (t_ast_complete_command *)malloc(
						sizeof(t_ast_complete_command))))
			exit_perror(ENOMEM, NULL);
		(*cc)->list = NULL;
		(*cc)->separator_op = NULL;
		if (ast_list(&((*cc)->list), tokens))
			ast_separator_op(&((*cc)->separator_op), tokens);
		else
		{
			free_ast_complete_command(*cc);
			*cc = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_complete_commands(t_ast_complete_commands **cc, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*cc = (t_ast_complete_commands *)malloc(
						sizeof(t_ast_complete_commands))))
			exit_perror(ENOMEM, NULL);
		(*cc)->complete_command = NULL;
		(*cc)->newline_list = NULL;
		(*cc)->complete_commands = NULL;
		if (ast_complete_command(&((*cc)->complete_command), tokens))
		{
			if (ast_newline_list(&((*cc)->newline_list), tokens))
				ast_complete_commands(&((*cc)->complete_commands), tokens);
		}
		else
		{
			free_ast_complete_commands(*cc);
			*cc = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ast_program(t_ast_program **program, t_list *tokens)
{
	if (tokens)
	{
		if (!(*program = (t_ast_program *)malloc(sizeof(t_ast_program))))
			exit_perror(ENOMEM, NULL);
		(*program)->linebreak = NULL;
		(*program)->complete_commands = NULL;
		(*program)->post_linebreak = NULL;
		ast_linebreak(&((*program)->linebreak), &tokens);
		if (ast_complete_commands(&((*program)->complete_commands), &tokens))
			ast_linebreak(&((*program)->post_linebreak),  &tokens);
		if (!(*program)->linebreak && !(*program)->complete_commands)
		{
			free_ast_program(*program);
			*program = NULL;
			return (0);
		}
		return (1);
	}
	return (-1);
}

t_ast_program	*make_ast(t_list *tokens)
{
	t_ast_program	*program;

	program = NULL;
	if (tokens)
	{
		ast_program(&program, tokens);
	}
	return (program);
}
