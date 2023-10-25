/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:02:14 by smokashi          #+#    #+#             */
/*   Updated: 2023/10/25 10:04:15 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	match(char *expected, t_shell *shell, char *string)
{
	if (ft_strlen(expected) != 0 && ft_strncmp(&string[shell->pos],
			expected, ft_strlen(expected)) == 0)
		shell->pos += ft_strlen(expected);
	else
	{
		shell->fail = 1;
		printf("Error: Unexpected '%c' at position %ld\n",
			string[shell->pos], shell->pos);
	}
}

void	pipeline(t_shell *shell, char *string)
{
	spaces(shell, string);
	shell->rdp_temp = shell->pos;
	simple_command(shell, string);
	spaces(shell, string);
	if (shell->pos == shell->rdp_temp)
		shell->fail = 1;
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
	shell->rdp_word = word(string, shell->pos);
	if (string[shell->pos] != '|' && ft_strlen(string) != shell->pos
		&& ft_strncmp(&string[shell->pos], shell->rdp_word,
			ft_strlen(shell->rdp_word)) == 0)
	{
		match(shell->rdp_word, shell, string);
		free(shell->rdp_word);
		cmd_suffix(shell, string);
	}
	free(shell->rdp_word);
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

void	cmd_suffix(t_shell *shell, char *string)
{
	spaces(shell, string);
	shell->rdp_word = word(string, shell->pos);
	if (ft_strncmp(&string[shell->pos], ">", 1) == 0
		|| ft_strncmp(&string[shell->pos], "<", 1) == 0)
	{
		free(shell->rdp_word);
		io_list(shell, string);
		cmd_suffix(shell, string);
	}
	else if (string[shell->pos] != '|' && ft_strlen(string) != shell->pos
		&& ft_strncmp(&string[shell->pos],
			shell->rdp_word, ft_strlen(shell->rdp_word)) == 0)
	{
		match(shell->rdp_word, shell, string);
		free(shell->rdp_word);
		cmd_suffix(shell, string);
	}
}
