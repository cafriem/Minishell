/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:14:52 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/25 15:36:03 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		g_exit_signal = 1;
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler2(int sig_num)
{
	(void)sig_num;
	g_exit_signal = 1;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", STDERR_FILENO);
	rl_replace_line("", 0);
	exit(200);
}

void	set_signal(void)
{
	signal(SIGINT, signal_handler2);
	signal(SIGQUIT, SIG_IGN);
}

void	check_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal(t_shell *shell, int flag)
{
	if (flag == 1)
	{
		remove_environment_variable(&shell->env, "OLDPWD");
		check_signal();
	}
	if (flag == 2)
	{
		if (g_exit_signal == 1)
		{
			shell->exit_code = 1;
			g_exit_signal = 0;
		}
	}
}
