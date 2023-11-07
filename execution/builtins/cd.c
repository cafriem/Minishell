/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:01:42 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/07 18:02:24 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	absolute_pathcase(t_shell *shell, int cmd_num)
{
	char	*home;
	char	**paths;
	char	*ab_path;

	home = getenv("HOME");
	paths = ft_split(shell->command[cmd_num].cmd_args[1], '~');
	ab_path = ft_strjoin(home, paths[0]);
	if (chdir(ab_path) < 0)
	{
		shell->exit_code = 1;
		perror(shell->command[cmd_num].cmd_args[1]);
	}
	free(paths[0]);
	free(paths);
	free(ab_path);
}

int	err_msg(t_shell *shell, int flag, int cmd_num)
{
	shell->exit_code = 1;
	if (flag == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd("OLDPWD not set\n", STDERR_FILENO);
	}
	else if (flag == 3)
	{
		shell->exit_code = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(shell->command[cmd_num].cmd_args[1]);
	}
	return (1);
}

int	ft_cd2(t_shell *shell, int cmd_num)
{
	if (ft_strcmp(shell->command[cmd_num].cmd_args[1], "~") == 0)
		chdir(getenv("HOME"));
	else if (ft_strcmp(shell->command[cmd_num].cmd_args[1], "-") == 0)
	{
		if (find_env(shell->env, "OLDPWD"))
		{
			if (chdir(find_env(shell->env, "OLDPWD")) < 0)
				return (err_msg(shell, 2, cmd_num));
			ft_pwd(shell, 0, 1);
		}
		else
			return (err_msg(shell, 2, cmd_num));
		change_path(shell);
	}
	return (ft_cd3(shell, cmd_num));
}

int	ft_cd3(t_shell *shell, int cmd_num)
{
	char	*pwd;

	if (chdir(shell->command[cmd_num].cmd_args[1]) < 0)
	{
		if (ft_strncmp(shell->command[cmd_num].cmd_args[1], "~", 1) == 0)
			absolute_pathcase(shell, cmd_num);
		else
			return (err_msg(shell, 3, cmd_num));
	}
	else
	{
		pwd = NULL;
		pwd = getcwd(pwd, 0);
		if (pwd == NULL)
			return (ft_pwd(shell, 0, 1));
		else
		{
			free(pwd);
			return (0);
		}
	}
	return (0);
}

int	ft_cd(t_shell *shell, int cmd_num)
{
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "cd") == 0)
	{
		if (shell->command[cmd_num].cmd_args[1] == NULL)
		{
			if (find_variable_val(shell->env, "HOME") == NULL)
				return (err_msg(shell, 1, cmd_num));
			chdir(getenv("HOME"));
		}
		else if (ft_cd2(shell, cmd_num) == 1)
			return (1);
		change_path(shell);
	}
	return (0);
}
