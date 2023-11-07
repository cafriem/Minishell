/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/07 19:30:58 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute(t_shell *shell)
{
	int		status;
	int		cmd_num;

	cmd_num = -1;
	shell->fd_tmp = dup(STDOUT_FILENO);
	start_executing(shell);
	dup2(shell->fd_tmp, STDOUT_FILENO);
	close_all_fd(shell);
	if (shell->fd_tmp != 0)
	{
		close (shell->fd_tmp);
		shell->fd_tmp = 0;
	}
	while (++cmd_num < shell->number_commands)
	{
		while (waitpid(shell->command[cmd_num].pid, &status, 0) > 0)
		{
			if (status == 127)
				shell->exit_code = 127;
			else if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
		}
	}
	check_signal(2);
	return (1);
}

void	start_executing(t_shell *shell)
{
	int	cmd_num;

	cmd_num = -1;
	while (++cmd_num < shell->number_commands)
	{
		if (here_doc_redi(shell, cmd_num) == 200)
		{
			g_exit_signal = 1;
			break ;
		}
		start_executing2(shell, cmd_num, 1);
		if (shell->number_commands == 1 && (is_builtin(shell, cmd_num)
				|| shell->command[cmd_num].cmd_args[0] == NULL))
		{
			if (redirection(shell, cmd_num) == -1)
			{
				g_exit_signal = 1;
				break ;
			}
			builtin_1(shell, cmd_num);
		}
		else
			start_executing2(shell, cmd_num, 0);
	}
}

void	start_executing2(t_shell *shell, int cmd_num, int flag)
{
	if (flag == 1)
	{
		if (shell->command[cmd_num].cmd_args[0] == NULL)
			shell->exit_code = 0;
		if (cmd_num != shell->number_commands - 1)
			if (pipe(shell->command[cmd_num].fd) == -1)
				exit(-1);
		if (shell->number_commands == 1
			&& shell->command[cmd_num].cmd_args[0] != NULL)
			if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "exit") == 0)
				ft_exit(shell, cmd_num);
	}
	else
		exc_cmd(shell, cmd_num);
}

void	exc_cmd(t_shell *shell, int cmd_num)
{
	shell->command[cmd_num].pid = fork();
	if (shell->command[cmd_num].pid < 0)
		perror("fork");
	else if (shell->command[cmd_num].pid == 0)
	{
		check_signal(2);
		if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "./minishell") == 0)
		{
			shell->env_joind = joind_env(shell);
			execve("./minishell", shell->command[cmd_num].cmd_args,
				shell->env_joind);
			ft_putstr_fd("minishell: ", 2);
			perror("execve");
			free_exit_child(shell);
			exit(errno);
		}
		exc_cmd_child(shell, cmd_num);
	}
}

void	exc_cmd_child(t_shell *shell, int cmd_num)
{
	if (shell->number_commands != 1)
		ft_dup2(shell, cmd_num);
	if (redirection(shell, cmd_num) == -1)
	{
		free_exit_child(shell);
		exit(1);
	}
	close_all_fd(shell);
	if (is_builtin(shell, cmd_num)
		|| (shell->command[cmd_num].cmd_args[0] == NULL
			&& shell->number_commands > 1))
		forked_builtin(shell, cmd_num);
	else
		forked_child(shell, cmd_num);
}
