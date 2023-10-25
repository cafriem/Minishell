/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:29:28 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/25 15:15:57 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	redirection_dup(t_shell *shell, int cmd_num, int i, int flag)
{
	shell->command[cmd_num].fd_redi = ft_open(shell,
			shell->command[cmd_num].redir[i].file, flag);
	if (shell->command[cmd_num].fd_redi == -1 && (shell->number_commands == 1
			|| shell->command[cmd_num].cmd_args[0] == NULL))
		return (-1);
	if (flag == APPEND || flag == RE_OUTPUT)
	{
		if (dup2(shell->command[cmd_num].fd_redi, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(-1);
		}
	}
	else if (flag == RE_INPUT && shell->command[cmd_num].cmd_args[0] != NULL
		&& !is_builtin(shell, cmd_num))
	{
		if (dup2(shell->command[cmd_num].fd_redi, STDIN_FILENO) < 0)
			exit(-1);
	}
	if (shell->command[cmd_num].fd_redi != 0)
	{
		close(shell->command[cmd_num].fd_redi);
		shell->command[cmd_num].fd_redi = 0;
	}
	return (0);
}

int	here_doc_redi2(t_shell *shell, int cmd_num, int lst_redi_pos)
{
	int	i;

	i = 0;
	while (i < shell->command[cmd_num].no_redir)
	{
		if (shell->command[cmd_num].redir[i].direct == HERE_DOC)
		{
			set_signal();
			if (i != lst_redi_pos)
				here_doc3(shell, cmd_num, i);
			else
				return (heredoc_exc(shell, cmd_num, i));
		}
		i++;
	}
	return (0);
}

int	here_doc_redi(t_shell *shell, int cmd_num)
{
	int	lst_redi_pos;
	int	pid;
	int	status;

	if (check_red(shell) == 1)
	{
		signal(SIGINT, SIG_IGN);
		lst_redi_pos = heredoc_pos(shell, cmd_num);
		pid = fork();
		if (pid < 0)
			perror("fork");
		else if (pid == 0)
		{
			here_doc_redi2(shell, cmd_num, lst_redi_pos);
			free_exit_child(shell);
			exit (0);
		}
		if (waitpid(pid, &status, 0) > -1)
		{
			check_signal();
			return (WEXITSTATUS(status));
		}
		return (0);
	}
	return (0);
}

void	is_heredoc(t_shell *shell, int cmd_num, int i)
{
	shell->command[cmd_num].fd_redi
		= open(shell->command[cmd_num].redir[i].file, O_RDWR, 0777);
	if (shell->command[cmd_num].fd_redi != -1)
	{
		if (shell->number_commands > 1 || (!is_builtin(shell, cmd_num)))
		{
			if (dup2(shell->command[cmd_num].fd_redi, STDIN_FILENO) < 0)
				exit(-1);
		}
		if (unlink(shell->command[cmd_num].redir[i].file) == -1)
			perror("unlink");
		if (shell->command[cmd_num].fd_redi != 0)
		{
			close(shell->command[cmd_num].fd_redi);
			shell->command[cmd_num].fd_redi = 0;
		}
	}
}

int	redirection(t_shell *shell, int cmd_num)
{
	int	i;

	i = 0;
	while (i < shell->command[cmd_num].no_redir)
	{
		if (shell->command[cmd_num].redir[i].direct == HERE_DOC)
			is_heredoc(shell, cmd_num, i);
		else if (shell->command[cmd_num].redir[i].direct == APPEND
			|| shell->command[cmd_num].redir[i].direct == RE_INPUT
			|| shell->command[cmd_num].redir[i].direct == RE_OUTPUT)
			if (redirection_dup(shell, cmd_num, i,
					shell->command[cmd_num].redir[i].direct) == -1)
				return (-1);
		i++;
	}
	return (0);
}
