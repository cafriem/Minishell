/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:14 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/02 12:43:19 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_open(t_shell *shell, char *str, int flag)
{
	int	fd;

	fd = 0;
	if (flag == RE_INPUT || flag == HERE_DOC)
		fd = open(str, O_RDWR, 0777);
	else if (flag == RE_OUTPUT)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (flag == APPEND)
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		shell->exit_code = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		if (shell->number_commands > 1)
		{
			free_exit_child(shell);
			exit (1);
		}
		return (-1);
	}
	return (fd);
}

void	first_cmd(t_shell *shell, int cmd_num)
{
	if (dup2(shell->command[cmd_num].fd[1], STDOUT_FILENO) < 0)
		exit(-1);
	close(shell->command[cmd_num].fd[1]);
	shell->command[cmd_num].fd[1] = 0;
}

void	last_cmd(t_shell *shell, int cmd_num)
{
	if (dup2(shell->command[cmd_num - 1].fd[0], STDIN_FILENO) < 0)
		exit(-1);
	close(shell->command[cmd_num - 1].fd[0]);
	shell->command[cmd_num - 1].fd[0] = 0;
}

void	middle_cmd(t_shell *shell, int cmd_num)
{
	if (dup2(shell->command[cmd_num - 1].fd[0], STDIN_FILENO) < 0)
		exit(-1);
	if (dup2(shell->command[cmd_num].fd[1], STDOUT_FILENO) < 0)
		exit(-1);
	close(shell->command[cmd_num - 1].fd[0]);
	close(shell->command[cmd_num].fd[1]);
	shell->command[cmd_num - 1].fd[0] = 0;
	shell->command[cmd_num].fd[1] = 0;
}

void	ft_dup2(t_shell *shell, int cmd_num)
{
	if (cmd_num == 0)
		first_cmd(shell, cmd_num);
	else if (cmd_num + 1 == shell->number_commands)
		last_cmd(shell, cmd_num);
	else
		middle_cmd(shell, cmd_num);
}
