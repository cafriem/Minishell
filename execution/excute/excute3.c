/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/08 11:20:26 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	builtin_1(t_shell *shell, int cmd_num)
{
	if (shell->command[cmd_num].cmd_args[0] != NULL)
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
		return (shell->exit_code);
	}
	return (1);
}

int	check_red(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->number_commands)
	{
		j = 0;
		while (j < shell->command[i].no_redir)
		{
			if (shell->command[i].redir[j].direct == HERE_DOC)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	path_free_split(char **cmd, char **path_split)
{
	ft_freesplit(cmd);
	ft_freesplit(path_split);
}

void	ft_check_sig(t_shell *shell)
{
	if (g_exit_signal == 1)
	{
		shell->exit_code = 1;
		g_exit_signal = 0;
	}
	if (g_exit_signal == 131)
	{
		shell->exit_code = 131;
		g_exit_signal = 0;
	}
	if (g_exit_signal == 130)
	{
		shell->exit_code = 130;
		g_exit_signal = 0;
	}
	save_tmp_pwd(shell);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
