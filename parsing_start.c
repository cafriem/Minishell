/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:20 by cafriem           #+#    #+#             */
/*   Updated: 2023/10/25 10:29:36 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution/execution.h"

void	temp_into_arg(t_shell *shell)
{
	char	*str;
	int		counter;

	counter = 0;
	while (shell->split_pipe[counter])
	{
		str = ft_strdup(shell->split_pipe[counter]);
		shell->command[counter].cmd_line = ft_strdupfree(str);
		ft_cmd_args(&shell->command[counter], shell->command[counter].cmd_line);
		ft_cmd_args_sp(&shell->command[counter]);
		ft_redirect(&shell->command[counter]);
		if (shell->command[counter].cmd_args[0] == NULL
			&& shell->command[counter].cmd_line[0] != '\0'
			&& shell->command[counter].no_redir == 0)
			shell->fail = 1;
		counter++;
	}
}

void	ft_setup(t_shell *shell, char *start)
{
	add_history (start);
	check_spmark (shell, start);
	shell->current_line = ft_strdup (start);
	free(start);
	ft_env (shell);
	if (shell->fail == 0)
		recursive_decent_parsing (shell, shell->current_line);
	if (shell->fail == 1)
	{
		printf("FAIL : CHECK INPUT\n");
		free(shell->current_line);
	}
	else
		start_work(shell);
}

void	start_work(t_shell *shell)
{
	shell->number_commands = splitcount(shell->current_line, '|');
	shell->split_pipe = ft_splitmini(shell->current_line, '|');
	shell->command = ft_calloc(splitcount
			(shell->current_line, '|'), sizeof(t_command));
	temp_into_arg(shell);
	if (shell->fail == 0)
		execute(shell);
	else
		printf("FAIL : CHECK INPUT\n");
	free_command_args(shell);
}

void	free_command_args(t_shell *shell)
{
	int	i;
	int	c;

	i = 0;
	while (i < shell->number_commands)
	{
		ft_freesplit(shell->command[i].cmd_args);
		c = 0;
		while (c < shell->command[i].no_redir)
		{
			free(shell->command[i].redir[c].file);
			c++;
		}
		free(shell->command[i].redir);
		free(shell->command[i].cmd_line);
		i++;
	}
	free(shell->command);
	free(shell->current_line);
	ft_freesplit(shell->env_joind);
	ft_freesplit(shell->split_pipe);
}

void	printstruct(t_shell *shell)
{
	int	i;
	int	c;

	i = 0;
	printf("-----PARSED-----\n");
	printf("num of commands = |%d|\n", shell->number_commands);
	while (i < shell->number_commands)
	{
		printf("cmd_line %d = |%s|\n", i, shell->command[i].cmd_line);
		c = 0;
		while (c < shell->command[i].no_args)
		{
			printf("command %d,%d= |%s|\n", 
				i, c, shell->command[i].cmd_args[c]);
			c++;
		}
		c = 0;
		while (c < shell->command[i].no_redir)
		{
			printf("redir  %d,%d = |%s|\n", i, c, shell->command[i].redir[c].file);
			printf("direct %d,%d = |%u|\n", i, c, shell->command[i].redir[c].direct);
			c++;
		}
		i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_shell		shell;
	char		*start;

	ft_bzero(&shell, sizeof(t_shell));
	ft_env_init(&shell, env);
	remove_environment_variable(&shell.env, "OLDPWD");
	check_signal();
	while (argc > 0 && argv[0])
	{
		shell.fail = 0;
		start = readline("\033[1;35mminishell> \033[0m");
		if (g_exit_signal == 1)
		{
			shell.exit_code = 1;
			g_exit_signal = 0;
		}
		if (start == NULL)
		{
			ft_putstr_fd("\033[1;35mMinishell> exit\033[0m\n", STDERR_FILENO);
			ft_env_free(&shell);
			return (0);
		}
		start = ft_strtrim_free(start, " ");
		if (*start == '\0')
		{
			free(start);
			continue ;
		}
		ft_setup(&shell, start);
	}
}
//newest version 16-10-2023
