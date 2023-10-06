/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/06 15:17:18 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	builtin_one(t_shell *shell, int cmd_num)
{
	if (ft_pwd(shell, cmd_num, 0) || ft_cd(shell, cmd_num) || 
		ft_unset(shell, cmd_num) || ft_env_exc(shell, cmd_num) || 
		ft_echo(shell, cmd_num) || ft_export(shell, cmd_num))
		return (1);
	else if (ft_exit(shell, cmd_num))
		return (1);
	return (0);
}

void	forked_builtin(t_shell *shell, int cmd_num)
{
	if (ft_pwd(shell, cmd_num, 0) || ft_cd(shell, cmd_num) || 
		ft_unset(shell, cmd_num) || ft_env_exc(shell, cmd_num) || 
		ft_echo(shell, cmd_num) || ft_export(shell, cmd_num))
	{
		close_all_fd(shell);
		exit (0);
	}
	else if (ft_exit(shell, cmd_num))
		exit(exit_code);
	close_all_fd(shell);
	exit_code = 1;
	exit(1);
}

int	builtin_pipe(t_shell *shell, int cmd_num)
{
	int	id;

	id = fork();
	if (id < 0)
		exit(-1);
	else if (id == 0)
	{
		if (shell->number_commands != 1)
			ft_dup2(shell, cmd_num);
		redirection(shell, cmd_num);
		forked_builtin(shell, cmd_num);
	}
	return (0);
}

int	is_builtin(t_shell *shell, int cmd_num)
{
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "pwd") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "cd") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "unset") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "env") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "exit") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "echo") == 0
		|| ft_strcmp(shell->command[cmd_num].cmd_args[0], "export") == 0)
		return (1);
	return (0);
}

void	check_infile_exc(t_shell *shell, int cmd_num)
{
	if (ft_strncmp(shell->command[cmd_num].cmd_args[0], "./", 2) == 0 
		&& strcmp(shell->command[cmd_num].cmd_args[0], "./minishell") != 0)
	{
		if (execve(shell->command[cmd_num].cmd_args[0], 
				shell->command[cmd_num].cmd_args, NULL) < 0)
		{
			perror(shell->command[cmd_num].cmd_args[0]);
			exit_code = errno;
			close_all_fd(shell);
			exit(errno);
		}
	}
}
