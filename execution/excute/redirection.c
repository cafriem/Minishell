/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:29:28 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/10 12:43:29 by cmrabet          ###   ########.fr       */
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

int	heredoc_pos(t_shell *shell, int cmd_num)
{
	int	i;

	i = shell->command[cmd_num].no_redir;
	while (i > -1)
	{
		if (shell->command[cmd_num].redir[i].direct == HERE_DOC)
			return (i);
		i--;
	}
	return (-1);
}

void	here_doc_redi(t_shell *shell, int cmd_num)
{
	int	lst_redi_pos;
	int	i;

	lst_redi_pos = heredoc_pos(shell, cmd_num);
	i = 0;
	while (i < shell->command[cmd_num].no_redir)
	{
		if (shell->command[cmd_num].redir[i].direct == HERE_DOC)
		{
			if (i != lst_redi_pos)
				here_doc3(shell, cmd_num, i);
			else
				heredoc_exc(shell, cmd_num, i);
		}
		i++;
	}
}

void	is_heredoc(t_shell *shell, int cmd_num, int i)
{
	shell->command[cmd_num].fd_redi = 
		ft_open(shell, shell->command[cmd_num].redir[i].file, RE_INPUT);
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

void	redirection(t_shell *shell, int cmd_num)
{
	int	i;

	i = 0;
	while (i < shell->command[cmd_num].no_redir)
	{
		if (shell->command[cmd_num].redir[i].direct == HERE_DOC 
			&& !is_builtin(shell, cmd_num))
			is_heredoc(shell, cmd_num, i);
		else if (shell->command[cmd_num].redir[i].direct == APPEND || 
			shell->command[cmd_num].redir[i].direct == RE_INPUT || 
			shell->command[cmd_num].redir[i].direct == RE_OUTPUT)
			redirection_dup(shell, cmd_num, i, 
				shell->command[cmd_num].redir[i].direct);
		i++;
	}
}
