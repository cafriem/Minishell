/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:00:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/07 19:29:57 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	exit_utils(t_shell *shell, int cmd_num)
{
	if (ft_str_isnum(shell->command[cmd_num].cmd_args[1]) != 0)
		exit_utils2(shell, shell->command[cmd_num].cmd_args[1]);
	else
	{
		shell->exit_code = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	}
}

void	exit_utils2(t_shell *shell, char *arg)
{
	shell->exit_code = 255;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_exit(shell);
}

void	free_exit(t_shell *shell)
{
	free_command_args(shell);
	ft_env_free(shell);
	exit(shell->exit_code);
}

int	ft_exit(t_shell *shell, int cmd_num)
{
	close_all_fd(shell);
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "exit") == 0
		&& shell->number_commands == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if (shell->command[cmd_num].no_args > 2)
			exit_utils(shell, cmd_num);
		else if (shell->command[cmd_num].no_args == 2)
		{
			shell->exit_code
				= ft_long(shell, cmd_num, shell->command[cmd_num].cmd_args[1]);
			if (ft_str_isnum(shell->command[cmd_num].cmd_args[1]) == 0
				&& ft_minpos_check(shell->command[cmd_num].cmd_args[1]) == 1
				&& shell->exit_code <= 9223372036854775807)
				free_exit(shell);
			else
				exit_utils2(shell, shell->command[cmd_num].cmd_args[1]);
		}
		else
			free_exit(shell);
		return (1);
	}
	return (0);
}
