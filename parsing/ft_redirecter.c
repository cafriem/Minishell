/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:31 by cafriem           #+#    #+#             */
/*   Updated: 2023/05/26 10:15:02 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

// void	redirect_str(char *string, t_command *command, int pos)
// {
// 	int	counter;
// 	int	start;

// 	counter = 0;
// 	start = 0;
// 	while (string[counter])
// 	{
// 		if (string[counter] == '\'' || string[counter] == '\"')
// 			counter += ft_skip_spmark(string, counter);
// 		else if (string[counter] == '>' && string[counter + 1] == '>')
// 		{
// 			command->redir[pos + 1].direct = APPEND;
// 			command->redir[pos].file = ft_substr(string, start, counter - 1);
// 			pos++;
// 			start = counter + 2;
// 			counter += 2;
// 		}
// 		else if (string[counter] == '<' && string[counter + 1] == '<')
// 		{
// 			command->redir[pos + 1].direct = HERE_DOC;
// 			command->redir[pos].file = ft_substr(string, start, counter - 1);
// 			pos++;
// 			start = counter + 2;
// 			counter += 2;
// 		}
// 		else if (string[counter] == '>')
// 		{
// 			command->redir[pos + 1].direct = RE_OUTPUT;
// 			command->redir[pos].file = ft_substr(string, start, counter - 1);
// 			pos++;
// 			start = counter + 1;
// 			counter += 1;
// 		}
// 		else if (string[counter] == '<')
// 		{
// 			command->redir[pos + 1].direct = RE_INPUT;
// 			command->redir[pos].file = ft_substr(string, start, counter - 1);
// 			pos++;
// 			start = counter + 1;
// 			counter += 1;
// 		}
// 		else
// 			counter++;
// 	}
// 	command->redir[pos].file = ft_substr(string, start, counter - 1);
// }

// void	red(char *string, t_command *command)
// {
// 	char	**newstr;
// 	int		w_c;
// 	int		l_c;
// 	int		pos;

// 	w_c = 0;
// 	l_c = 0;
// 	pos = 0;
// 	newstr = ft_splitmini(string, ' ');
// 	while (newstr[w_c])
// 	{
// 		if (newstr[w_c][0] == '<' || newstr[w_c][0] == '>')
// 		{
// 			if (newstr[w_c][0] == '>' && newstr[w_c][1] == '>')
// 			{
// 				command->redir[pos].direct = APPEND;
// 				if (newstr[w_c][3] != '\0')
// 				{
// 					redirect_str(newstr[w_c + 1], &command, pos);
// 					w_c++;
// 				}
// 				else if (newstr[w_c + 1] && (newstr[w_c + 1][0] != '<' || newstr[w_c + 1][0] != '>'))
// 				{
// 					newstr[w_c] = ft_substr(newstr[w_c], 3, ft_strlen(newstr[w_c]));
// 					redirect_str(newstr[w_c], &command, pos);
// 				}
// 				pos++;
// 				// else
// 				// 	FAIL ADD A FAIL PARSE ERROR
// 			}
// 			else if (newstr[w_c][0] == '<' && newstr[w_c][1] == '<')
// 			{
// 				command->redir[pos].direct = HERE_DOC;
// 				if (newstr[w_c][3] != '\0')
// 					command->redir[pos].file = ft_substr(newstr[w_c], 3, ft_strlen(newstr[w_c]));
// 				else if (newstr[w_c + 1])
// 					command->redir[pos].file = ft_strdup(newstr[w_c + 1]);
// 				pos++;
// 			}
// 			else if (newstr[w_c][0] == '>')
// 			{
// 				command->redir[pos].direct = RE_OUTPUT;
// 				if (newstr[w_c][2] != '\0')
// 					command->redir[pos].file = ft_substr(newstr[w_c], 2, ft_strlen(newstr[w_c]));
// 				else if (newstr[w_c + 1])
// 					command->redir[pos].file = ft_strdup(newstr[w_c + 1]);
// 				pos++;
// 			}
// 			else if (newstr[w_c][0] == '<')
// 			{
// 				command->redir[pos].direct = RE_INPUT;
// 				if (newstr[w_c][2] != '\0')
// 					command->redir[pos].file = ft_substr(newstr[w_c], 2, ft_strlen(newstr[w_c]));
// 				else if (newstr[w_c + 1])
// 					command->redir[pos].file = ft_strdup(newstr[w_c + 1]);
// 				pos++;
// 			}
// 		}
// 		w_c++;
// 	}
// }

void	redir_temp(char *string, t_command *command)
{
	int	counter;

	counter = 0;
	start = 0;
	while (string[counter])
	{
		if (string[counter] == ' ')
		{
			
		}
	}
}

void	ft_redirect(t_command *command)
{
	int	counter;
	int	c;

	counter = 0;
	c = redirect_counter(&command->temp[0]);
	printf("$$$ redirect counter = %d \n", c);
	command->redir = ft_calloc(c, sizeof(t_direct));
	// printf("calloc \n");
	// red(&command->temp, &command);
	redir_temp(&command->temp, &command);
	// printf("finished \n");
}

//< t1 grep yes > r
