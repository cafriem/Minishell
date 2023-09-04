/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:31 by cafriem           #+#    #+#             */
/*   Updated: 2023/09/04 14:30:45 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*filename(t_command *command, char *string, int start)
{
	int	counter;

	while (string[start] == ' ')
		start++;
	counter = start;
	while (string[counter])
	{
		if (string[counter] == '"' || string[counter] == '\'')
			counter += ft_skip_spmark(string, counter);
		else if (ft_strchr(" <>|", string[counter]) != NULL)
		{
			command->int_temp = counter;
			return (ft_substr(string, start, counter - start));
		}
		else
			counter++;
	}
	command->int_temp = counter;
	return (ft_substr(string, start, counter - start));
}

void	ft_heredoc_append(char *string, t_command *command, int start)
{
	char	*temp;
	char	*temper;

	if ((string[start] == '>' && string[start + 1] == '>')
		|| (string[start] == '<' && string[start + 1] == '<'))
	{
		if (string[start] == '>' && string[start + 1] == '>')
			command->redir[command->no_redir].direct = APPEND;
		else if (string[start] == '<' && string[start + 1] == '<')
			command->redir[command->no_redir].direct = HERE_DOC;
		temp = filename(command, string, start + 2);
		temper = ft_strdupfree(sp_remover(temp));
		free(temp);
		command->redir[command->no_redir].file = ft_strdupfree(temper);
	}
}

void	redirect_temp(char *string, t_command *command, int start)
{
	char	*temp;

	if ((string[start] == '>' && string[start + 1] == '>')
		|| (string[start] == '<' && string[start + 1] == '<'))
		ft_heredoc_append(string, command, start);
	else if (string[start] == '>' || string[start] == '<')
	{
		if (string[start] == '>')
			command->redir[command->no_redir].direct = RE_OUTPUT;
		if (string[start] == '<')
			command->redir[command->no_redir].direct = RE_INPUT;
		temp = filename(command, string, start + 1);
		command->redir[command->no_redir].file = ft_strdupfree(
				sp_remover(temp));
		free(temp);
	}
	command->no_redir++;
}

void	redir_temp(char *string, t_command *command)
{
	int	counter;

	counter = 0;
	command->int_temp = 0;
	command->no_redir = 0;
	while (string[counter])
	{
		if (string[counter] == ' ')
		{
			while (string[counter] == ' ')
				counter++;
		}
		else if (string[counter] == '\'' || string[counter] == '"')
			counter += ft_skip_spmark(string, counter);
		else if (string[counter] == '>' || string[counter] == '<')
		{
			redirect_temp(string, command, counter);
			counter = command->int_temp;
		}
		else
			counter++;
	}
}

void	ft_redirect(t_command *command)
{
	int	redir_count;

	redir_count = redirect_counter(command->cmd_line) + 1;
	command->redir = ft_calloc(redir_count, sizeof(t_direct));
	command->no_redir = redirect_counter(command->cmd_line);
	redir_temp(command->cmd_line, command);
}
