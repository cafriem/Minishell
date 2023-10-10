/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:45:40 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/10 12:48:16 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_str_ne(char *c)
{
	int	i;

	i = 1;
	if (c[0] != '-' || c[1] == '\0')
		return (1);
	while (c[i])
	{
		if (c[i] != 'n' && c[i] != 'e')
			return (1);
		++i;
	}
	return (0);
}

void	ft_echo_2(t_shell *shell, int cmd_num)
{
	int	i;
	int	flag;

	i = 1;
	flag = 2;
	while (i < shell->command[cmd_num].no_args 
		&& ft_str_ne(shell->command[cmd_num].cmd_args[i]) == 0)
	{
		i++;
		flag = 1;
	}
	while (i < shell->command[cmd_num].no_args)
	{
		ft_putstr_fd(shell->command[cmd_num].cmd_args[i], STDOUT_FILENO);
		if (i < shell->command[cmd_num].no_args - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag == 2)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	ft_echo(t_shell *shell, int cmd_num)
{
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "echo") == 0)
	{
		if (shell->command[cmd_num].no_args == 1)
		{
			ft_putchar_fd('\0', STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			return (1);
		}
		ft_echo_2(shell, cmd_num);
		shell->exit_code = 0;
		return (1);
	}
	return (0);
}
