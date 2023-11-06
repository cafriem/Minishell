/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 08:42:58 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/06 16:00:03 by cmrabet          ###   ########.fr       */
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
		if (pwd == NULL && flag == 0)
		{
			ft_putstr_fd(shell->pwd_tmp, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			return (1);
		}
		else if (pwd == NULL && flag == 1)
		{
			pwd = ft_strjoin(shell->pwd_tmp, "/..");
			shell->pwd_tmp = ft_strdup(pwd);
			ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", STDOUT_FILENO);
			free(pwd);
			return (1);
		}
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(pwd);
	}
	return (0);
}

void	change_path(t_shell *shell)
{
	char	*pwd_value;
	char	*path;

	pwd_value = find_env(shell->env, "PWD");
	path = NULL;
	if (pwd_value)
	{
		path = getcwd(path, 0);
		update_env(shell, pwd_value, path);
		free(path);
		path = NULL;
	}
}
