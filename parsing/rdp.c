/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:19:03 by cafriem           #+#    #+#             */
/*   Updated: 2023/06/12 21:24:32 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	match(char *expected, t_shell *shell, char *string)
{
	if (ft_strncmp(&string[shell->pos], expected, ft_strlen(expected)) == 0)
		shell->pos += strlen(expected);
	else
	{
		printf("Error: Expected '%s' at position %ld\n", expected, shell->pos);
		exit(1);
	}
}

void	pipeline(t_shell *shell, char *string)
{
	spaces(shell, string);
	simple_command(shell, string);
}

void	simple_command(t_shell *shell, char *string)
{
	spaces(shell, string);
	io_list(shell, string);
}

void	io_list(t_shell *shell, char *string)
{
	spaces(shell, string);
	if (ft_strncmp(&string[shell->pos], ">", 1) == 0
		|| ft_strncmp(&string[shell->pos], "<", 1) == 0)
	{
		io_redirect(shell, string);
		io_list(shell, string);
	}
}

void	io_redirect(t_shell *shell, char *string)
{
	spaces(shell, string);
	if (ft_strncmp(&string[shell->pos], "<", 1) == 0)
	{
		match("<", shell, string);
		match(word(string, shell->pos), shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], ">", 1) == 0)
	{
		match(">", shell, string);
		match(word(string, shell->pos), shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], ">>", 2) == 0)
	{
		match(">>", shell, string);
		match(word(string, shell->pos), shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], "<<", 2) == 0)
	{
		match("<<", shell, string);
		match(word(string, shell->pos), shell, string);
	}
}

char	*word(char *string, int start)
{
	int	counter;

	counter = start;
	while (ft_strchr(" <>", string[counter]) == NULL)
	{
		counter++;
		if (string[counter] == '\'' || string[counter] == '"')
			counter += ft_skip_spmark(string, counter);
	}
	return (ft_substr(string, start, counter - start));
}

void	spaces(t_shell *shell, char *string)
{
	while (string[shell->pos] == ' ')
		shell->pos++;
}

int	main(void)
{
	t_shell	shell;
	char	*string;

	shell.pos = 0;
	string = ft_strdup("< grep testing > t2");
	pipeline(&shell, string);

	if (shell.pos == ft_strlen(string))
		printf("Parsing successful.\n");
	else
		printf("Error: Unexpected token at position %ld\n", shell.pos);
}
