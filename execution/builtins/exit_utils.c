/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:00:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/07 19:22:00 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_str_isnum(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '+' || c[i] == '-')
		i++;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (1);
		++i;
	}
	return (0);
}

long	ft_res(t_shell *shell, int cmd_num, int c1, const char *str)
{
	long	c;

	c = 0;
	while (str[c1] >= '0' && str[c1] <= '9')
	{
		if ((c >= 922337203685477580 && str[c1] > '7')
			|| c >= 9223372036854775807 || c < 0)
			exit_utils2(shell, shell->command[cmd_num].cmd_args[1]);
		c = (c * 10) + (str[c1] - 48);
		c1++;
	}
	if (c < 0)
		exit_utils2(shell, shell->command[cmd_num].cmd_args[1]);
	return (c);
}

long	ft_long(t_shell *shell, int cmd_num, const char *str)
{
	long	c1;
	int		minus;

	c1 = 0;
	minus = 1;
	if (str[c1] == '-' || str[c1] == '+')
	{
		if (str[c1] == '-')
			minus = -1;
		c1++;
	}
	return (minus * ft_res(shell, cmd_num, c1, str));
}

int	ft_minpos_check(char *str)
{
	int	c;
	int	c1;

	c = 0;
	c1 = 0;
	while (str[c1] == '-' || str[c1] == '+')
	{
		c++;
		c1++;
	}
	if (c1 > 1)
		return (0);
	return (1);
}
