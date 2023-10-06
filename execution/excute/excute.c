/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/06 15:18:09 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute(t_shell *shell)
{
	shell->fd_tmp = dup(STDOUT_FILENO);
	start_executing(shell);
	dup2(shell->fd_tmp, STDOUT_FILENO);
	close_all_fd(shell);
	if (shell->fd_tmp != 0)
	{
		close (shell->fd_tmp);
		shell->fd_tmp = 0;
	}
	while (waitpid(-1, &exit_code, 0) > -1)
		exit_code = WEXITSTATUS(exit_code);
	return (1);
}

void	start_executing(t_shell *shell)
{
	int	cmd_num;

	cmd_num = 0;
	while (cmd_num < shell->number_commands 
		&& shell->command[cmd_num].cmd_args[0])
	{
		here_doc_redi(shell, cmd_num);
		if (cmd_num != shell->number_commands - 1)
		{
			if (pipe(shell->command[cmd_num].fd) == -1)
				exit(-1);
		}
		if (shell->number_commands == 1 && 
			ft_strcmp(shell->command[cmd_num].cmd_args[0], "exit") == 0)
			ft_exit(shell, cmd_num);
		else if (is_builtin(shell, cmd_num))
			builtin_pipe(shell, cmd_num);
		else
		{
			exc_cmd(shell, cmd_num);
		}
		cmd_num++;
	}
}

void	forked_child(t_shell *shell, int cmd_num)
{
	char	*cmd_path;

	check_infile_exc(shell, cmd_num);
	cmd_path = find_path(shell->command[cmd_num].cmd_args[0]);
	if (execve(cmd_path, shell->command[cmd_num].cmd_args, 
			shell->env_joind) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->command[cmd_num].cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(shell->env_joind);
	}
	exit_code = 127;
	exit(127);
}

void	exc_cmd(t_shell *shell, int cmd_num)
{
	int	id;

	id = fork();
	if (id < 0)
		perror("fork");
	else if (id == 0)
	{
		shell->env_joind = joind_env(shell);
		if (strcmp(shell->command[cmd_num].cmd_args[0], "./minishell") == 0)
		{
			execve("./minishell", shell->command[cmd_num].cmd_args, 
				shell->env_joind);
			ft_putstr_fd("minishell: ", 2);
			perror("execve");
			free(shell->env_joind);
			exit(1);
		}
		if (shell->number_commands != 1)
			ft_dup2(shell, cmd_num);
		redirection(shell, cmd_num);
		close_all_fd(shell);
		forked_child(shell, cmd_num);
	}
}
