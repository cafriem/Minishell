/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:04:37 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/12 09:10:03 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

int	builtin(t_shell *shell)
{
	if (ft_strcmp(shell->command[0].cmd_line, "pwd"))
		ft_pwd();
	else if (ft_strcmp(shell->command[0].cmd_line, "pwd"))
	else
		return (1);
	
	return (0);
}