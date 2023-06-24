/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:20 by cafriem           #+#    #+#             */
/*   Updated: 2023/06/12 21:15:23 by cafriem          ###   ########.fr       */
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
		shell->command[counter].cmd_line = ft_strdup(shell->split_pipe[counter]);
		ft_redirect(&shell->command[counter]);
		ft_cmd_args(&shell->command[counter], shell->command[counter].cmd_line);
		counter++;
	}
}

int	main(void)
{
	char		*start;
	int			cmd;
	t_shell		shell;

	start = "<012 \"678 10jij\" dhwaihda | < test hellos ";
	recursive_decent_parsing(&shell, start);
	shell.current_line = ft_strdup(start);
	check_spmark(shell.current_line);
	// env stuff
	shell.split_pipe = ft_splitmini(shell.current_line, '|');
	cmd = splitcount(shell.current_line, '|');
	shell.command = ft_calloc(cmd, sizeof(t_command));
	temp_into_arg(&shell);
	// printf("$$$ 0. %s\n", shell.command[0].temp);
	// printf("$$$ 1. %s\n", shell.command[1].temp);
	// printf("$$$ seperating\n");
	printf("-----PARSED-----\n");
	printf("cmd_line = |%s|\n", shell.command[0].cmd_line);
	printf("cmd_line = |%s|\n", shell.command[1].cmd_line);
	printf("file = |%s|\n", shell.command[0].redir[0].file);
	printf("file = |%s|\n", shell.command[1].redir[0].file);
	printf("command = |%s|\n", shell.command[0].cmd_args[0]);
	printf("command = |%s|\n", shell.command[0].cmd_args[1]);
	printf("command = |%s|\n", shell.command[0].cmd_args[2]);
	printf("command = |%s|\n", shell.command[1].cmd_args[0]);
}
