/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:31 by cafriem           #+#    #+#             */
/*   Updated: 2023/06/08 16:44:57 by cafriem          ###   ########.fr       */
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

// void	redirect_str(char *string, t_command *command)
// {
// 	int	counter;
// 	int	start;
// 	counter = 0;
// 	start = 0;
// 	// if (string[counter] == '\0')
// 	// 	PRINT FAIL OR SMT
// 	while (string[counter])
// 	{
// 		if (string[counter] == '\'' || string[counter] == '\"')
// 			counter += ft_skip_spmark(string, counter);
// 		else if (string[counter] == '>' && string[counter + 1] == '>')
// 		{
// 			command->redir[command->redir_amount].direct = APPEND;
// 			command->redir[command->redir_amount].file = ft_substr(string, start, counter - 1);
// 			command->redir_amount++;
// 			start = counter + 2;
// 			counter += 2;
// 		}
// 		else if (string[counter] == '<' && string[counter + 1] == '<')
// 		{
// 			command->redir[command->redir_amount].direct = HERE_DOC;
// 			command->redir[command->redir_amount].file = ft_substr(string, start, counter - 1);
// 			command->redir_amount++;
// 			start = counter + 2;
// 			counter += 2;
// 		}
// 		else if (string[counter] == '>')
// 		{
// 			command->redir[command->redir_amount].direct = RE_OUTPUT;
// 			command->redir[command->redir_amount].file = ft_substr(string, start, counter - 1);
// 			command->redir_amount++;
// 			start = counter + 1;
// 			counter += 1;
// 		}
// 		else if (string[counter] == '<')
// 		{
// 			command->redir[command->redir_amount].direct = RE_INPUT;
// 			command->redir[command->redir_amount].file = ft_substr(string, start, counter - 1);
// 			command->redir_amount++;
// 			start = counter + 1;
// 			counter += 1;
// 		}
// 		else
// 			counter++;
// 	}
// 	command->redir[command->redir_amount].file = ft_substr(string, start, counter - 1);
// }

// void	red(char *string, t_command *command)
// {
// 	char	**newstr;
// 	int		w_c;
// 	w_c = 0;
// 	command->redir_amount = 0;
// 	newstr = ft_splitmini(string, ' ');
// 	while (newstr[w_c])
// 	{
// 		if (redirect_counter(newstr[w_c]) > 0)
// 			redirect_str(newstr[w_c], &command);
// 		w_c++;
// 	}
// }

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
	printf("string = %s\n", newstr);
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
		else if (string[counter] == ' ')
		{
			command->int_temp = counter;
			printf("news = %s\n", filename2(string, start, counter - start));
			return (filename2(string, start, counter - start));
		}
		else
			counter++;
	}
	printf("news = %s\n", filename2(string, start, counter - start));
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
	int	start;

	start = 0;
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
	printf("$$$ redirect strings = %s \n", command->temp);
	command->redir = ft_calloc(redirect_counter(command->temp) + 1, sizeof(t_direct));
	redir_temp(&command->temp[0], command);
}
