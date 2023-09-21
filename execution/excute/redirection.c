/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:29:28 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/21 14:21:17 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	redirection_dup(t_shell *shell, int cmd_num,int i, int flag)
{
	shell->command[cmd_num].fd_redi = ft_open(shell->command[cmd_num].redir[i].file, flag);
	if (flag == APPEND || flag == RE_OUTPUT) 
	{
		if (dup2(shell->command[cmd_num].fd_redi, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(-1);
		}
	}
	else if (flag == RE_INPUT && !is_builtin(shell, cmd_num))
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

int	redirection(t_shell *shell, int cmd_num)
{
	int	i;

	i = 0;
	while (i < shell->command[cmd_num].no_redir)
	{
		redirection_dup(shell, cmd_num,i, shell->command[cmd_num].redir[i].direct);
		i++;
	}
	return (1);
}
