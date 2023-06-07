/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:20 by cafriem           #+#    #+#             */
/*   Updated: 2023/06/07 13:28:42 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_opr_counter(const char *c)
{
	int	op_counter;
	int	sp_mark;
	int	s_mark;
	int	i;

	op_counter = 0;
	sp_mark = 0;
	s_mark = 0;
	i = 0;
	while (c[i])
	{
		if (c[i] == '\'')
			s_mark++;
		if (c[i] == '"')
			sp_mark++;
		while ((s_mark % 2 != 0 || sp_mark % 2 != 0) && c[i])
		{
			i++;
			if (c[i] == '\'')
				s_mark++;
			if (c[i] == '"')
				sp_mark++;
			// if (!c[i])
			// 	return (0);
		}
		if ((c[i] == '>' && c[i + 1] == '>') || (c[i] == '<' && c[i + 1] == '<'))
		{
			op_counter++;
			i += 2;
		}
		else if (c[i] == '>' || c[i] == '<' || c[i] == '|')
		{
			op_counter++;
			i++;
		}
		else
			i++;
	}
	return (op_counter);
}

void	temp_into_arg(t_shell *shell)
{
	int	counter;

	counter = 0;
	while (shell->split_pipe[counter])
	{
		shell->command[counter].temp = ft_strdup(shell->split_pipe[counter]);
		counter++;
	}
}

int	main(void)
{
	char		*start;
	int			cmd;
	t_shell		shell;

	start = "< 234567 export x=\"cd\" > t2| grep monomo";
	shell.line = ft_strdup(ft_strtrim(start, " "));
	cmd = splitcount(shell.line, '|');
	shell.split_pipe = ft_splitmini(shell.line, '|');
	check_spmarks(&shell, cmd);
	shell.command = ft_calloc(cmd, sizeof(t_command));
	temp_into_arg(&shell);
	printf("$$$ 0. %s\n", shell.command[0].temp);
	printf("$$$ 1. %s\n", shell.command[1].temp);
	printf("$$$ seperating\n");
	ft_redirect(&shell.command[0]);
	printf("file = |%s|\n", shell.command[0].redir[0].file);
	printf("file = |%s|\n", shell.command[0].redir[1].file);
	// ft_redirecter(string, command);
}
