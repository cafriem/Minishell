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
#include <readline/history.h>
#include <readline/readline.h>

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

char	*sp_remover(char *str)
{
	char	*sp;
	char	skip;
	size_t	counter;
	int	c;

	counter = 0;
	while (str[counter] && (str[counter] != '\'' && str[counter] != '"'))
		counter++;
	skip = str[counter];
	if (ft_strlen(str) != counter)
	{
		sp = ft_substr(str, 0, counter);
		c = ft_strlen(ft_strchr(str, skip)) - ft_strlen(ft_strrchr(str, skip));
		sp = ft_strjoinfree(sp, ft_substr(str, counter + 1, c - 1), 3);
		c = ft_strlen(str) - ft_strlen(ft_strrchr(str, skip));
		sp = ft_strjoinfree(sp, ft_substr(str, c + 1, ft_strlen(str)), 3);
		return(sp);
	}
	return(str);
}

t_shell		shell;

int	main()
{
	char		*start;
	int			cmd;
	// t_shell		shell;

	start = ft_strdup("<11|8");
	check_spmark(start);
	recursive_decent_parsing(&shell, start);
	shell.current_line = ft_strdup(start);
	// env stuff
	shell.split_pipe = ft_splitmini(shell.current_line, '|');
	cmd = splitcount(shell.current_line, '|');
	shell.command = ft_calloc(cmd, sizeof(t_command));
	temp_into_arg(&shell);
	printf("-----PARSED-----\n");
	// printf("$$$ 0. %s\n", shell.command[0].temp);
	// printf("$$$ 1. %s\n", shell.command[1].temp);
	// printf("$$$ seperating\n");
	printf("cmd_line = |%s|\n", shell.command[0].cmd_line);
	printf("cmd_line = |%s|\n", shell.command[1].cmd_line);
	printf("file = |%s|\n", shell.command[0].redir[0].file);
	printf("command 0,0= |%s|\n", shell.command[0].cmd_args[0]);
	printf("command 0,1= |%s|\n", shell.command[0].cmd_args[1]);
	printf("command 1,0= |%s|\n", shell.command[1].cmd_args[0]);
}
