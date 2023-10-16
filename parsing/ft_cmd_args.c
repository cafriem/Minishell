/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:01:05 by smokashi          #+#    #+#             */
/*   Updated: 2023/10/16 12:27:29 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	filename_skip(char *string, int start)
{
	int	counter;

	counter = start;
	while (string[counter] == ' ')
		counter++;
	while (string[counter])
	{
		if (string[counter] == '"' || string[counter] == '\'')
			counter += ft_skip_spmark(string, counter);
		else if (ft_strchr(" <>|", string[counter]) != NULL)
			return (counter - start);
		else
			counter++;
	}
	return (counter - start);
}

char	*ft_cmd_strjoin(char *temp, char *wordres)
{
	temp = ft_strjoinfree(temp, " ", 1);
	temp = ft_strjoinfree(temp, wordres, 3);
	return (temp);
}

char	*ft_cmd_args_list(t_command *command, char *string, int counter)
{
	char	*temp;
	char	*wordres;

	temp = NULL;
	while (string[counter])
	{
		while (string[counter] == ' ')
			counter++;
		if (string[counter] == '<' || string[counter] == '>')
			counter += skip_redirect(string, counter);
		else if (string[counter])
		{
			wordres = word(string, counter);
			counter += ft_strlen(wordres);
			if (command->int_temp == 0)
				temp = ft_strdupfree(wordres);
			else
				temp = ft_cmd_strjoin(temp, wordres);
			command->int_temp++;
		}
		else
			counter++;
	}
	return (temp);
}

void	ft_cmd_args(t_command *command, char *string)
{
	char	*temp;

	command->int_temp = 0;
	temp = ft_cmd_args_list(command, string, 0);
	if (command->int_temp > 1)
		command->cmd_args = ft_splitmini(temp, ' ');
	else
	{
		command->cmd_args = ft_calloc(2, sizeof(char *));
		if (temp == NULL)
			command->cmd_args[0] = temp;
		else
			command->cmd_args[0] = ft_strdup(temp);
	}
	command->no_args = command->int_temp;
	if (temp)
		free(temp);
}

void	ft_cmd_args_sp(t_command *command)
{
	char	*string;
	int		counter;

	counter = 0;
	while (counter < command->no_args)
	{
		string = ft_strdup(command->cmd_args[counter]);
		free (command->cmd_args[counter]);
		command->cmd_args[counter] = sp_remover(string);
		free(string);
		counter++;
	}
}
