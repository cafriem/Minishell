/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:14:52 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/07 19:49:03 by cmrabet          ###   ########.fr       */
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
	close(STDIN_FILENO);
}

void	signal_handler3(int sig_num)
{
	if (sig_num == SIGINT)
		g_exit_signal = 130;
	else
		g_exit_signal = 131;
}

void	check_signal(int flag)
{
	if (flag == 1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 2)
	{
		signal(SIGINT, signal_handler3);
		signal(SIGQUIT, signal_handler3);
	}
	else if (flag == 3)
	{
		signal(SIGINT, signal_handler2);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ft_signal(t_shell *shell)
{
	remove_environment_variable(&shell->env, "OLDPWD");
	check_signal(1);
}
