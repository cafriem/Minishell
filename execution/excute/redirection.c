/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:29:28 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/12 16:22:15 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	redirection_dup(t_shell *shell, int cmd_num, int i, int flag)
{
	shell->command[cmd_num].fd_redi = 
		ft_open(shell, shell->command[cmd_num].redir[i].file, flag);
	if (flag == APPEND || flag == RE_OUTPUT) 
	{
		if (dup2(shell->command[cmd_num].fd_redi, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(-1);
		}
	}
	else if (flag == RE_INPUT)
	{
		if (dup2(shell->command[cmd_num].fd_redi, STDIN_FILENO) < 0)
			exit(-1);
	}
	if (shell->command[cmd_num].fd_redi != 0)
	{
		close(shell->command[cmd_num].fd_redi);
		shell->command[cmd_num].fd_redi = 0;
	}
}

void	here_doc_redi2(t_shell *shell, int cmd_num, int lst_redi_pos)
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
				exit(heredoc_exc(shell, cmd_num, i));
		}
		i++;
	}
}

int	here_doc_redi(t_shell *shell, int cmd_num)
{
	int	lst_redi_pos;
	int	pid;
	int	status;

	signal(SIGINT, SIG_IGN);
	lst_redi_pos = heredoc_pos(shell, cmd_num);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		here_doc_redi2(shell, cmd_num, lst_redi_pos);
		free_command_args(shell);
		ft_env_free(shell);
		exit (0);
	}
	if (waitpid(pid, &status, 0) > -1)
	{
		check_signal();
		return (WEXITSTATUS(status));
	}
	check_signal();
	return (0);
}

void	is_heredoc(t_shell *shell, int cmd_num, int i)
{
	shell->command[cmd_num].fd_redi = 
		open(shell->command[cmd_num].redir[i].file, O_RDWR, 0777);
	if (shell->command[cmd_num].fd_redi != -1)
	{
		if (dup2(shell->command[cmd_num].fd_redi, STDIN_FILENO) < 0)
			exit(-1);
		if (unlink(shell->command[cmd_num].redir[i].file) == -1) 
			perror("unlink");
		if (shell->command[cmd_num].fd_redi != 0)
		{
			close(shell->command[cmd_num].fd_redi);
			shell->command[cmd_num].fd_redi = 0;
		}
	}
}

void	redirection(t_shell *shell, int cmd_num)
{
	int	i;

	i = 0;
	while (i < shell->command[cmd_num].no_redir)
	{
		if (shell->command[cmd_num].redir[i].direct == HERE_DOC)
			is_heredoc(shell, cmd_num, i);
		else if (shell->command[cmd_num].redir[i].direct == APPEND || 
			shell->command[cmd_num].redir[i].direct == RE_INPUT || 
			shell->command[cmd_num].redir[i].direct == RE_OUTPUT)
			redirection_dup(shell, cmd_num, i, 
				shell->command[cmd_num].redir[i].direct);
		i++;
	}
}
