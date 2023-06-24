/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:31 by cafriem           #+#    #+#             */
/*   Updated: 2023/06/09 16:19:56 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	next_redir(char *string, int start)
{
	while (string[start])
	{
		if (string[start] == '>' || string[start] == '<')
			return (start);
		start++;
	}
	return (start);
}

int	redirect_counter(char *string)
{
	int	redirector;
	int	c;

	c = 0;
	redirector = 0;
	while (string[c])
	{
		if ((string[c] == '>' && string[c + 1] == '>')
			|| (string[c] == '<' && string[c + 1] == '<'))
		{
			c += 2;
			redirector++;
		}
		else if (string[c] == '>' || string[c] == '<')
		{
			c++;
			redirector++;
		}
		else if (string[c] == '\'' || string[c] == '\"')
			c += ft_skip_spmark(string, c);
		else
			c++;
	}
	return (redirector);
}

char	*filename2(char *string, int start, int amount)
{
	int		counter;
	int		c;
	char	*newstr;

	counter = start;
	c = 0;
	while(counter < (amount + start))
	{
		if (string[counter] == '"' || string[counter] == '\"')
			c++;
		counter++;
	}
	if (c == 0)
		return (ft_substr(string, start, counter - start));
	newstr = ft_calloc(amount - c, sizeof(char));
	counter = start;
	c = 0;
	while (counter < (amount + start))
	{
		if (string[counter] != '"' || string[counter] != '\"')
		{
			newstr[c] = string[counter];
			c++;
		}
		counter++;
	}
	return (newstr);
}

char	*filename(t_command *command, char *string, int start)
{
	int	counter;

	counter = start;
	while (string[counter] == ' ')
	{
		start++;
		counter++;
	}
	start = counter;
	while (string[counter])
	{
		if (string[counter] == '"' || string[counter] == '\'')
			counter += ft_skip_spmark(string, counter);
		else if (ft_strchr(" <>|", string[counter]) != NULL)
		{
			command->int_temp = counter;
			return (filename2(string, start, counter - start));
		}
		else
			counter++;
	}
	command->int_temp = counter;
	return (filename2(string, start, counter - start));
}

// fix the " mark for file names

void	redirect_temp(char *string, t_command *command, int start)
{
	if (string[start] == '>' && string[start + 1] == '>')
	{
		command->redir[command->redir_amount].direct = APPEND;
		command->redir[command->redir_amount].file = filename(command , string, start + 2);
		command->redir_amount++;
	}
	else if (string[start] == '<' && string[start + 1] == '<')
	{
		command->redir[command->redir_amount].direct = HERE_DOC;
		command->redir[command->redir_amount].file = filename(command ,string, start + 2);
		command->redir_amount++;
	}
	else if (string[start] == '>')
	{
		command->redir[command->redir_amount].direct = RE_OUTPUT;
		command->redir[command->redir_amount].file = filename(command ,string, start + 1);
		command->redir_amount++;
	}
	else if (string[start] == '<')
	{
		command->redir[command->redir_amount].direct = RE_OUTPUT;
		command->redir[command->redir_amount].file = filename(command ,string, start + 1);
		command->redir_amount++;
	}
}

void	redir_temp(char *string, t_command *command)
{
	int	counter;

	counter = 0;
	command->int_temp = 0;
	command->redir_amount = 0;
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
	command->redir = ft_calloc(redirect_counter(command->cmd_line) + 1, sizeof(t_direct));
	redir_temp(command->cmd_line, command);
}
