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
	printf("expected : '%s'\n", expected);
	if (ft_strlen(expected) != 0 && ft_strncmp(&string[shell->pos],
			expected, ft_strlen(expected)) == 0) 
		shell->pos += ft_strlen(expected);
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
	spaces(shell, string);
	if (ft_strncmp(&string[shell->pos], "|", 1) == 0)
	{
		match("|", shell, string);
		pipeline(shell, string);
	}
}

void	simple_command(t_shell *shell, char *string)
{
	spaces(shell, string);
	io_list(shell, string);
	if (string[shell->pos] != '|' && ft_strlen(string) != shell->pos
		&& ft_strncmp(&string[shell->pos], word(string, shell->pos),
		ft_strlen(word(string, shell->pos))) == 0)
	{
		match(word(string, shell->pos), shell, string);
		cmd_suffix(shell, string);
	}
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

void cmd_suffix(t_shell *shell, char *string)
{
	spaces(shell, string);
	if (ft_strncmp(&string[shell->pos], ">", 1) == 0
		|| ft_strncmp(&string[shell->pos], "<", 1) == 0)
	{
		io_list(shell, string);
		cmd_suffix(shell, string);
	}
	else if (ft_strlen(string) != shell->pos && ft_strncmp(&string[shell->pos],
		word(string, shell->pos), ft_strlen(word(string, shell->pos))) == 0)
	{
		match(word(string, shell->pos), shell, string);
		cmd_suffix(shell, string);
	}
}

void	io_redirect(t_shell *shell, char *string)
{
	spaces(shell, string);
	if (ft_strncmp(&string[shell->pos], ">>", 2) == 0)
	{
		match(">>", shell, string);
		spaces(shell, string);
		match(word(string, shell->pos), shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], "<<", 2) == 0)
	{
		match("<<", shell, string);
		spaces(shell, string);
		match(word(string, shell->pos), shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], ">", 1) == 0)
	{
		match(">", shell, string);
		spaces(shell, string);
		match(word(string, shell->pos), shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], "<", 1) == 0)
	{
		match("<", shell, string);
		spaces(shell, string);
		match(word(string, shell->pos), shell, string);
	}
}

char	*word(char *string, int start)
{
	int	counter;

	counter = start;
	while (ft_strchr(" <>|", string[counter]) == NULL)
	{
		if (string[counter] == '\'' || string[counter] == '"')
			counter += ft_skip_spmark(string, counter);
		else
			counter++;
	}
	return (ft_substr(string, start, counter - start));
}

void	spaces(t_shell *shell, char *string)
{
	while (string[shell->pos] == ' ')
		shell->pos++;
}

void	recursive_decent_parsing(t_shell *shell, char *string)
{
	pipeline(&shell, string);

	if (shell->pos == ft_strlen(string))
		printf("Parsing successful.\n");
	else
		printf("Error: Unexpected token at position %ld\n", shell->pos);
}
