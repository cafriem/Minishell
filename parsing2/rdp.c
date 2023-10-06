/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:19:03 by cafriem           #+#    #+#             */
/*   Updated: 2023/09/04 14:35:06 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	io_redirect_continue(t_shell *shell, char *string)
{
	spaces(shell, string);
	shell->rdp_word = word(string, shell->pos);
	match(shell->rdp_word, shell, string);
	free(shell->rdp_word);
}

void	io_redirect(t_shell *shell, char *string)
{
	spaces(shell, string);
	if (ft_strncmp(&string[shell->pos], ">>", 2) == 0)
	{
		match(">>", shell, string);
		io_redirect_continue(shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], "<<", 2) == 0)
	{
		match("<<", shell, string);
		io_redirect_continue(shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], ">", 1) == 0)
	{
		match(">", shell, string);
		io_redirect_continue(shell, string);
	}
	else if (ft_strncmp(&string[shell->pos], "<", 1) == 0)
	{
		match("<", shell, string);
		io_redirect_continue(shell, string);
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
	shell->pos = 0;
	pipeline(shell, string);
	if (shell->pos != ft_strlen(string))
	{
		shell->fail = 1;
		printf("Error: Unexpected token at position %ld\n", shell->pos);
	}
}
