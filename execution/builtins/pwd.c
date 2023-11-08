/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 08:42:58 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/08 11:41:03 by cmrabet          ###   ########.fr       */
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
		if ((pwd == NULL && flag == 0))
		{
			ft_putstr_fd(shell->pwd_tmp, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			return (1);
		}
		else if (pwd == NULL && flag == 1)
		{
			shell->pwd_tmp = ft_strjoin(shell->pwd_tmp, "/..");
			ft_pwd2();
			return (1);
		}
		printf("ttttt: %s\n", pwd);
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

void	ft_pwd2(void)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ",
		STDOUT_FILENO);
	ft_putstr_fd("cd: error retrieving current directory:",
		STDOUT_FILENO);
	ft_putstr_fd(" getcwd: cannot access\n", STDOUT_FILENO);
}

void	update_env(t_shell *shell, char *old_pwd, char *new_pwd)
{
	save_tmp_pwd(shell);
	add_environment_variable(&(shell->env), "OLDPWD", old_pwd);
	add_environment_variable(&(shell->env), "PWD", new_pwd);
}

void	save_tmp_pwd(t_shell *shell)
{
	char	*tmp_pwd;

	tmp_pwd = NULL;
	tmp_pwd = getcwd(tmp_pwd, 0);
	if (tmp_pwd != NULL)
	{
		if (ft_strcmp(tmp_pwd, "../"))
			shell->pwd_tmp = tmp_pwd;
		free(tmp_pwd);
	}
}
