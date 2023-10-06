/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:14:52 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/06 09:34:24 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit_code = 1;
	}
}

void	check_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
