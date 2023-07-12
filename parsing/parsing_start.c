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

void	temp_into_arg(t_shell *shell)
{
	int	counter;

	counter = 0;
	while (shell->split_pipe[counter])
	{
		shell->command[counter].cmd_line = ft_strdup(shell->split_pipe[counter]);
		ft_redirect(&shell->command[counter]);
		ft_cmd_args(&shell->command[counter], shell->command[counter].cmd_line);
		// the error is here
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


int	main(int argc, char *argv[], char *env[])
{
	// t_shell		shell;
	// char		*start;
	// int			cmd;

	printf("%d", argc);
	printf("%s\n", argv[0]);
	ft_env_init(&shell.env, env);
	// start = ft_strdup("12\"54\'75\"76 >utfu ugiu");
	// check_spmark(start);
	// // ft_env(&shell, env);
	// recursive_decent_parsing(&shell, start);
	// shell.current_line = ft_strdup(start);
	// // env stuff
	// shell.split_pipe = ft_splitmini(shell.current_line, '|');
	// cmd = splitcount(shell.current_line, '|');
	// shell.command = ft_calloc(cmd, sizeof(t_command));
	// temp_into_arg(&shell);
	// printf("-----PARSED-----\n");
	// printf("cmd_line = |%s|\n", shell.command[0].cmd_line);
	// // printf("cmd_line = |%s|\n", shell.command[1].cmd_line);
	// printf("file = |%s|\n", shell.command[0].redir[0].file);
	// printf("command 0,0= |%s|\n", shell.command[0].cmd_args[0]);
	// printf("redirect 0,0= |%s|\n", shell.command[0].redir[0].file);
	// printf("command 0,1= |%s|\n", shell.command[0].cmd_args[1]);
	// printf("command 1,0= |%s|\n", shell.command[1].cmd_args[0]);
}
