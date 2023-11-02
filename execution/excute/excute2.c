/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/02 13:46:56 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	forked_builtin(t_shell *shell, int cmd_num)
{
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "pwd") == 0)
		shell->exit_code = ft_pwd(shell, cmd_num, 0);
	else if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "cd") == 0)
		shell->exit_code = ft_cd(shell, cmd_num);
	else if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "unset") == 0)
		shell->exit_code = ft_unset(shell, cmd_num);
	else if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "env") == 0)
		shell->exit_code = ft_env_exc(shell, cmd_num);
	else if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "echo") == 0)
		shell->exit_code = ft_echo(shell, cmd_num);
	else if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "export") == 0)
		shell->exit_code = ft_export(shell, cmd_num);
	else if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "exit") == 0)
		shell->exit_code = ft_exit(shell, cmd_num);
	free_exit_child(shell);
	exit(shell->exit_code);
}

void	builtin_pipe(t_shell *shell, int cmd_num)
{
	int	id;

	id = fork();
	if (id < 0)
		exit(-1);
	else if (id == 0)
	{
		if (shell->number_commands != 1)
			ft_dup2(shell, cmd_num);
		if (redirection(shell, cmd_num) == -1)
		{
			free_exit_child(shell);
			exit(1);
		}
		close_all_fd(shell);
		forked_builtin(shell, cmd_num);
	}
}

int	is_builtin(t_shell *shell, int cmd_num)
{
	if (shell->command[cmd_num].cmd_args[0] != NULL)
	{
		if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "pwd") == 0
			|| ft_strcmp(shell->command[cmd_num].cmd_args[0], "cd") == 0
			|| ft_strcmp(shell->command[cmd_num].cmd_args[0], "unset") == 0
			|| ft_strcmp(shell->command[cmd_num].cmd_args[0], "env") == 0
			|| ft_strcmp(shell->command[cmd_num].cmd_args[0], "exit") == 0
			|| ft_strcmp(shell->command[cmd_num].cmd_args[0], "echo") == 0
			|| ft_strcmp(shell->command[cmd_num].cmd_args[0], "export") == 0)
			return (1);
	}
	return (0);
}

void	check_infile_exc(t_shell *shell, int cmd_num)
{
	if (ft_strncmp(shell->command[cmd_num].cmd_args[0], "./", 2) == 0
		&& strcmp(shell->command[cmd_num].cmd_args[0], "./minishell") != 0)
	{
		if (execve(shell->command[cmd_num].cmd_args[0],
				shell->command[cmd_num].cmd_args, shell->env_joind) < 0)
		{
			check_stat(shell, shell->command[cmd_num].cmd_args[0]);
		}
	}
}

void	free_exit_child(t_shell *shell)
{
	close_all_fd(shell);
	free_command_args(shell);
	ft_env_free(shell);
}
