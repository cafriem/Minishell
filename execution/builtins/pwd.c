/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 08:42:58 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/14 11:43:06 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_pwd(t_shell *shell, int cmd_num, int flag)
{
	char	*pwd;

	pwd = NULL;
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "pwd") == 0 || flag == 1)
	{
		pwd = getcwd(pwd, 0);
		if (pwd == NULL)
		{
			perror("Minishell: ");
			return (1);
		}
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	return (0);
}
