/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/25 10:57:36 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	builtin_1(t_shell *shell, int cmd_num)
{
	if (shell->command[cmd_num].cmd_args[0] != NULL)
	{
		if (ft_pwd(shell, cmd_num, 0) || ft_cd(shell, cmd_num)
			|| ft_unset(shell, cmd_num) || ft_env_exc(shell, cmd_num)
			|| ft_echo(shell, cmd_num) || ft_export(shell, cmd_num))
			return (0);
		return (0);
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

void path_free_split(char **cmd, char **path_split)
{
		ft_freesplit(cmd);
		ft_freesplit(path_split);
}
